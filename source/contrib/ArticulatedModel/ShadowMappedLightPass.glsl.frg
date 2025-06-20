/**
  @file ShadowMappedLightPass.glsl.frg
  @author Morgan McGuire matrix@graphics3d.com

  For use with G3D::SuperShader.
 */

/** World space, normalized (TODO: non-directional light) */
uniform vec4        lightPosition;
uniform vec3        lightColor;

#ifdef SPECULARCONSTANT
    uniform vec3        specularConstant;
#endif

#ifdef SPECULARMAP
    uniform sampler2D   specularMap;
#endif

#ifdef SPECULAREXPONENTCONSTANT
    uniform vec3        specularExponentConstant;
#endif

#ifdef SPECULAREXPONENTMAP
    uniform sampler2D   specularExponentMap;
#endif

#if defined(DIFFUSECONSTANT)
    uniform vec3        diffuseConstant;
#endif

#ifdef DIFFUSEMAP
    uniform sampler2D   diffuseMap;
#endif

/** Set to -1 to flip the normal. */
uniform float       backside;

uniform sampler2DShadow shadowMap;

// World parameters
varying vec3        wsEyePos;
varying vec2        texCoord;

#ifdef NORMALBUMPMAP
    /** Multiplier for bump map.  Typically on the range [0, 0.05]
      This increases with texture scale and bump height. */
    uniform float       bumpMapScale;

    /** xyz = normal, w = bump height */
    uniform sampler2D   normalBumpMap;

    /** Un-normalized (interpolated) tangent space eye vector */
    varying vec3        _tsE;

	varying vec4        tan_X, tan_Y;
#endif

varying vec4        tan_Z, tan_W;

/** Coordinate to use in the shadow map */
varying vec4        shadowCoord;

/** Used for "ambient occlusion" */
varying float       accessibility;

void main(void) {
    vec3 wsEyePos = g3d_CameraToWorldMatrix[3].xyz;

#   ifdef NORMALBUMPMAP
        // Convert bumps to a world space distance
        float  bump   = (texture2D(normalBumpMap, texCoord).w - 0.5) * bumpMapScale;

	    vec3 tsE = normalize(_tsE);

        // Offset the texture coord.  Note that texture coordinates are inverted (in the y direction)
	    // from TBN space, so we must flip the y-axis.

        vec2 offsetTexCoord = texCoord.xy + vec2(tsE.x, -tsE.y) * bump;

	    // note that the columns might be slightly not orthogonal due to interpolation
	    mat4 tangentToWorld = mat4(tan_X, tan_Y, tan_Z, tan_W);
	    
        // Take the normal map values back to (-1, 1) range to compute a tangent space normal
        vec3 tsN = ((texture2D(normalBumpMap, offsetTexCoord).xyz - vec3(0.5, 0.5, 0.5)) * 2.0);

	    // Take the normal to world space 
	    vec3 wsN = (tangentToWorld * vec4(tsN, 0.0)).xyz * backside;

#   else
        vec2 offsetTexCoord = texCoord;

        // World space normal
        vec3 wsN = tan_Z.xyz * backside;
#   endif

	// or... (tangentToWorld * vec4(tsE, 0.0)).xyz;

    // Light vector      
	vec3 wsL = normalize(lightPosition.xyz - tan_W.xyz * lightPosition.w);

#   if defined(SPECULARCONSTANT) || defined(SPECULARMAP)
        // Eye vector
        vec3 wsE = wsEyePos - tan_W.xyz;

        // Reflection vector
        vec3 wsR = normalize((wsN * 2.0 * dot(wsN, wsE)) - wsE);
#   endif

#   if (defined(DIFFUSECONSTANT) || defined(DIFFUSEMAP))
        vec4 diffuseColor =
#       ifdef DIFFUSECONSTANT
            vec4(diffuseConstant, 1.0)
#           ifdef DIFFUSEMAP
                * texture2D(diffuseMap, offsetTexCoord)
#           endif
#       else
            texture2D(diffuseMap, offsetTexCoord)
#       endif
        ;
#   endif


#   if defined(SPECULARCONSTANT) || defined(SPECULARMAP)     
        vec4 specularColor =
#       ifdef SPECULARCONSTANT
            vec4(specularConstant, 1.0)
#           ifdef SPECULARMAP
                * texture2D(specularMap, offsetTexCoord)
#          endif
#       else
            texture2D(specularMap, offsetTexCoord)
#       endif
        ;
#   endif


#   if defined(SPECULAREXPONENTCONSTANT) || defined(SPECULAREXPONENTMAP)     
        vec4 specularExponentColor =
#       ifdef SPECULAREXPONENTCONSTANT
            vec4(specularExponentConstant, 1.0)
#           ifdef SPECULAREXPONENTMAP
                * texture2D(specularExponentMap, offsetTexCoord)
#           endif
#       else
            texture2D(specularExponentMap, offsetTexCoord)
#       endif
        ;
#   else
        vec4 specularExponentColor = vec4(1.0, 1.0, 1.0, 1.0);
#   endif

    // Compute projected shadow coord.
    vec4 projShadowCoord = shadowCoord / shadowCoord.w;

	// Used to produce vectors to the 8-neighbors, which leads to a smoother
	// shadow result
    vec4 s = vec4(g3d_sampler2DInvSize(shadowMap), -g3d_sampler2DInvSize(shadowMap).x, 0.0);
    vec4 d = s * 0.71;

    vec3 shadow =
         (shadow2D(shadowMap, projShadowCoord.xyz).rgb +
         
          shadow2D(shadowMap, projShadowCoord.xyz + s.xww).rgb +
          shadow2D(shadowMap, projShadowCoord.xyz - s.xww).rgb +
          shadow2D(shadowMap, projShadowCoord.xyz + s.wyw).rgb +
          shadow2D(shadowMap, projShadowCoord.xyz - s.wyw).rgb +

          shadow2D(shadowMap, projShadowCoord.xyz + d.xyw).rgb +
          shadow2D(shadowMap, projShadowCoord.xyz - d.zyw).rgb +
          shadow2D(shadowMap, projShadowCoord.xyz + d.zyw).rgb +
          shadow2D(shadowMap, projShadowCoord.xyz - d.xyw).rgb) / 9.0;

    gl_FragColor.rgb =
            accessibility * lightColor * shadow *
        ( 
#          if defined(DIFFUSECONSTANT) || defined(DIFFUSEMAP)
                // Diffuse
                max(dot(wsL, wsN), 0.0) 
                * diffuseColor.rgb
#          endif

#       if defined(SPECULARCONSTANT) || defined(SPECULARMAP)
            + pow(vec3(max(dot(wsL, wsR), 0.0)), specularExponentColor.rgb) * specularColor.rgb
#       endif
            );

    gl_FragColor.a = 1.0

#       if defined(DIFFUSECONSTANT) || defined(DIFFUSEMAP)
           * diffuseColor.a
#       endif

#       if defined(SPECULARCONSTANT) || defined(SPECULARMAP)
            * specularColor.a
#       endif

#       if defined(SPECULAEXPONENTRCONSTANT) || defined(SPECULAREXPONENTMAP)
            * specularExponentColor.a
#       endif
        ;
}

