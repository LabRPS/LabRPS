#ifndef MACROS_H
#define MACROS_H

#define BASIC_ACCESSOR(type, var, method, Method) \
  type method() const { return var; };            \
  void set##Method(const type value) { var = value; }
#define CLASS_ACCESSOR(type, var, method, Method) \
  type method() const { return var; };            \
  void set##Method(const type& value) { var = value; }

#endif  // MACROS_H
