// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
//  IOSReflection.h
//  JreEmulation
//
//  Created by Tom Ball on 9/23/13.
//

#ifndef JreEmulation_IOSReflection_h
#define JreEmulation_IOSReflection_h

#import <Foundation/Foundation.h>

// C data structures that hold "raw" metadata for use by the methods that
// implement Java reflection. This information is necessary because not
// all information provided by the reflection API is discoverable via the
// Objective-C runtime.

enum J2OBJC_ATTRIBUTE_TYPES {
  CONSTANT_VALUE,
  ENCLOSING_METHOD,
  EXCEPTIONS,
  GENERIC_SIGNATURE,
  INNER_CLASSES,
};

// Use same data types that the translator generates.
typedef union J2ObjcConstantValue {
  BOOL boolean;
  char byte;
  unichar char_;
  double double_;
  float float_;
  int int_;
  long long long_;
  short short_;
  const char *string;
} J2ObjcConstantValue;

// This type isn't actually used, but just defines the header shared
// by all attributes.
typedef struct J2ObjcAttribute {
  uint16_t attribute_type;
  uint16_t length;
} J2ObjCAttribute;

typedef struct J2ObjcConstantValueAttribute {
  uint16_t attribute_type;  // CONSTANT_VALUE
  uint16_t length;          // sizeof(J2ObjcConstantValue) + 4
  J2ObjcConstantValue constant;
} J2ObjcConstantValueAttribute;

typedef struct J2ObjcEnclosingMethodAttribute {
  uint16_t attribute_type;  // ENCLOSING_METHOD
  uint16_t length;          // sizeof(id) + 4
  const char *selector;
} J2ObjcAnnotationDefaultAttribute;

typedef struct J2ObjcExceptionsAttribute {
  uint16_t attribute_type;  // EXCEPTIONS
  uint16_t length;          // count * sizeof(id) + 6
  uint16_t count;
  const char **exception_classnames;
} J2ObjcExceptionAttribute;

typedef struct J2ObjcGenericSignatureAttribute {
  uint16_t attribute_type;  // GENERIC_SIGNATURE
  uint16_t length;          // sizeof(id) + 4
  const char *selector;
} J2ObjcGenericSignatureAttribute;

typedef struct J2ObjcInnerClassAttribute {
  uint16_t attribute_type;  // INNER_CLASSES
  uint16_t length;          // count * sizeof(id) + 6
  uint16_t count;
  const char **exception_classnames;
} J2ObjcInnerClassAttribute;

typedef struct J2ObjcMethodInfo {
  const char *selector;
  const char *javaName;
  const char *returnType;
} J2ObjcMethodInfo;

typedef struct J2ObjcClassInfo {
  const char *typeName;
  const char *packageName;
  const char *enclosingName;
  uint16_t modifiers;
  uint16_t methodCount;
  const J2ObjcMethodInfo *methods;
  uint16_t attribute_count;
  // Inner classes, enclosing method, generic signature.
  const J2ObjCAttribute *attributes;
} J2ObjcClassInfo;

typedef struct J2ObjcMemberInfo {
  const char *name;
  uint16_t modifiers;
  uint16_t attribute_count;
  // Fields: constant value, generic signature.
  // Methods: exceptions, generic signature,.
  const J2ObjCAttribute *attributes;
} J2ObjcMemberInfo;

// Autoboxing support.

// A raw value is the union of all possible native types.
typedef union {
  void *asId;
  char asChar;
  unichar asUnichar;
  short asShort;
  int asInt;
  long long asLong;
  float asFloat;
  double asDouble;
  BOOL asBOOL;
} J2ObjcRawValue;

#endif
