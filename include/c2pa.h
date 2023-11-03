// Copyright 2023 Adobe. All rights reserved.
// This file is licensed to you under the Apache License,
// Version 2.0 (http://www.apache.org/licenses/LICENSE-2.0)
// or the MIT license (http://opensource.org/licenses/MIT),
// at your option.

// Unless required by applicable law or agreed to in writing,
// this software is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR REPRESENTATIONS OF ANY KIND, either express or
// implied. See the LICENSE-MIT and LICENSE-APACHE files for the
// specific language governing permissions and limitations under
// each license.

// This file is generated by cbindgen, do not edit by hand.

#ifndef c2pa_bindings_h
#define c2pa_bindings_h

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64)
    #if defined(_STATIC_C2PA) 
        #define IMPORT  __declspec(dllexport)
    #else 
        #if __GNUC__
            #define IMPORT __attribute__ ((dllimport))
        #else
            #define IMPORT __declspec(dllimport)
        #endif
    #endif
#else
    #define IMPORT

#endif

/**
 * Defines the configuration for a Signer
 *
 * The signer is created from the signcert and pkey fields.
 * an optional url to an RFC 3161 compliant time server will ensure the signature is timestamped
 *
 */
typedef struct C2paSignerInfo {
  /**
   * The signing algorithm
   */
  const char *alg;
  /**
   * The public certificate chain in PEM format
   */
  const char *sign_cert;
  /**
   * The private key in PEM format
   */
  const char *private_key;
  /**
   * The timestamp authority URL or NULL
   */
  const char *ta_url;
} C2paSignerInfo;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * Returns a version string for logging
 *
 * # Safety
 * The returned value MUST be released by calling release_string
 * and it is no longer valid after that call.
 */
IMPORT extern char *c2pa_version(void);

/**
 * Returns the last error message
 *
 * # Safety
 * The returned value MUST be released by calling release_string
 * and it is no longer valid after that call.
 */
IMPORT extern char *c2pa_error(void);

/**
 * Returns a ManifestStore JSON string from a file path.
 * Any thumbnails or other binary resources will be written to data_dir if provided
 *
 * # Errors
 * Returns NULL if there were errors, otherwise returns a JSON string
 * The error string can be retrieved by calling c2pa_error
 *
 * # Safety
 * Reads from null terminated C strings
 * The returned value MUST be released by calling release_string
 * and it is no longer valid after that call.
 */
IMPORT extern char *c2pa_read_file(const char *path, const char *data_dir);

/**
 * Returns an Ingredient JSON string from a file path.
 * Any thumbnail or c2pa data will be written to data_dir if provided
 *
 * # Errors
 * Returns NULL if there were errors, otherwise returns a JSON string
 * containing the Ingredient
 * The error string can be retrieved by calling c2pa_error
 *
 * # Safety
 * Reads from null terminated C strings
 * The returned value MUST be released by calling release_string
 * and it is no longer valid after that call.
 */
IMPORT extern char *c2pa_read_ingredient_file(const char *path, const char *data_dir);

/**
 * Add a signed manifest to the file at path using auth_token
 * If cloud is true, upload the manifest to the cloud
 *
 * # Errors
 * Returns an error field if there were errors
 *
 * # Safety
 * Reads from null terminated C strings
 * The returned value MUST be released by calling release_string
 * and it is no longer valid after that call.
 */
IMPORT extern
char *c2pa_sign_file(const char *source_path,
                     const char *dest_path,
                     const char *manifest,
                     struct C2paSignerInfo signer_info,
                     const char *data_dir);

/**
 * Releases a string allocated by Rust
 *
 * # Safety
 * Reads from null terminated C strings
 * The string must not have been modified in C
 * can only be released once and is invalid after this call
 */
IMPORT extern void c2pa_release_string(char *s);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif /* c2pa_bindings_h */
