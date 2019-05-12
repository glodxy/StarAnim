#version 330 core
#define POINT_LIGHTS_NUM 4
#define SPOT_LIGHTS_NUM 4
#define TEXTURE_DIFFUSE_NUM 5
#define TEXTURE_SPECULAR_NUM 5
#define TEXTURE_NORMAL_NUM 5
struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    float opacity;
};

struct BaseLight{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirLight{
    BaseLight base;
    vec3 direction;
};

struct PointLight{
    vec3 position;
    BaseLight base;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight{
    float innercutoff;
    float outercutoff;
    vec3 direction;

    PointLight base;
};

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in vec4 FragPosLightSpace;

out vec4 color;


uniform bool blinn;

vec4 ambientOriginColor;
vec4 diffuseOriginColor;
vec4 specularOriginColor;

uniform int pointLightSize;
uniform int spotLightSize;
uniform int textureDiffuseSize=0;
uniform int textureSpecularSize=0;
uniform Material material=Material(vec3(0.5,0.5,0.5),vec3(1.0,1.0,1.0),vec3(0.0,0.0,0.0),0,1.0);
uniform DirLight dirLight;
uniform PointLight pointLights[POINT_LIGHTS_NUM];
uniform SpotLight spotLights[SPOT_LIGHTS_NUM];
uniform vec3 viewPos;

uniform sampler2D shadowMap;
uniform sampler2D texture_diffuse[TEXTURE_DIFFUSE_NUM];
uniform sampler2D texture_specular[TEXTURE_SPECULAR_NUM];


float CalcShadowFactor(vec4 LightSpacePos){
    vec3 projCoords=LightSpacePos.xyz/LightSpacePos.w;
    projCoords=0.5*projCoords+0.5;
    if(projCoords.z>1.0)
        return 0.0;
    float depth=texture(shadowMap,projCoords.xy).r;
    float curDepth=projCoords.z;
    float bias = 0.005;
    float shadow=curDepth-bias>depth?0.0:1.0;
    return shadow;
}

vec4 CalcNormalLight(BaseLight light,vec3 lightDirection,vec3 normal,float shadowFactor){
    vec4 ambientColor=vec4(light.ambient*material.ambient,1.0f);
    float diffuseFactor=dot(normal,-lightDirection);

    vec4 diffuseColor=vec4(0,0,0,0);
    vec4 specularColor=vec4(0,0,0,0);

    if(diffuseFactor>0){
        diffuseColor=vec4(light.diffuse*material.diffuse*diffuseFactor,1.0f);

        vec3 viewDir=normalize(viewPos-FragPos);
        vec3 reflectDir=normalize(reflect(lightDirection,normal));

        float specularFactor;
        if(blinn){
            vec3 halfDir=normalize(-lightDirection+viewDir);
            specularFactor=dot(halfDir,normal);
        }
        else {
            specularFactor=dot(viewDir, reflectDir);
        }
        if(specularFactor>0){
            if(blinn){
                specularFactor=pow(specularFactor,2*material.shininess);
                specularColor=vec4(light.specular*material.specular,1.0)*specularFactor;
            }
            else{
                specularFactor=pow(specularFactor,material.shininess);
                specularColor=vec4(light.specular*material.specular,1.0)*specularFactor;
            }
        }
    }
    //return diffuseColor*diffuseOriginColor;
    return (ambientColor*ambientOriginColor+shadowFactor*(diffuseColor*diffuseOriginColor+specularColor*specularOriginColor));
}

vec4 HandleDirLight(DirLight light,vec3 normal,vec4 lightSpacePos){
    float shadowFactor=CalcShadowFactor(lightSpacePos);
    return CalcNormalLight(light.base,light.direction,normal,shadowFactor);
}

vec4 HandlePointLight(PointLight light,vec3 normal,vec4 lightSpacePos){
    vec3 lightDirection=FragPos-light.position;
    float distance=length(lightDirection);
    lightDirection=normalize(lightDirection);
    float shadowFactor=CalcShadowFactor(lightSpacePos);

    vec4 color=CalcNormalLight(light.base,lightDirection,normal,shadowFactor);
    float attenuation=light.constant+light.linear*distance+light.quadratic*distance*distance;

    return color/attenuation;
}

vec4 HandleSpotLight(SpotLight light,vec3 normal,vec4 lightSpacePos){
    vec3 lightDir=normalize(FragPos-light.base.position);


    float theta=dot(lightDir,normalize(-light.direction));
    float epsilon=light.innercutoff-light.outercutoff;
    float intensity=clamp((theta-light.outercutoff)/epsilon,0.0,1.0);

    vec4 color=HandlePointLight(light.base,normal,lightSpacePos);
    return color*intensity;
}

void main()
{ 
    vec3 norm=normalize(Normal);

    ambientOriginColor=vec4(1.0,1.0,1.0,1.0);
    diffuseOriginColor=vec4(1.0,1.0,1.0,1.0);
    if(textureDiffuseSize>0){
        diffuseOriginColor=texture(texture_diffuse[0],TexCoords);
        ambientOriginColor=diffuseOriginColor;
    }

    if(textureSpecularSize>0){
        specularOriginColor=texture(texture_specular[0],TexCoords);
    }
    else{
        specularOriginColor=diffuseOriginColor;
    }


    vec4 result=HandleDirLight(dirLight,norm,FragPosLightSpace);
//    for(int i=0;i<pointLightSize;++i){
//        result+=HandlePointLight(pointLights[i],norm,FragPosLightSpace);
//    }
//
//     for(int i=0;i<spotLightSize;++i){
//         result+=HandleSpotLight(spotLights[i],norm,FragPosLightSpace);
//     }

    float s=CalcShadowFactor(FragPosLightSpace);

    color= vec4(result.rgb,diffuseOriginColor.a*material.opacity);
}