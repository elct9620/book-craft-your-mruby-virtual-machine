#include<mvm.h>
#include<tgc.h>

void mrb_define_method(RClass* klass, const char* name, mrb_func_t func) {
  int ret;
  khiter_t key = kh_put(mt, klass->mt, name, &ret);
  kh_value(klass->mt, key) = func;
}

void mrb_free_class(void* ptr) {
  RClass* klass = (RClass*)ptr;
  kh_destroy(mt, klass->mt);
}

RClass* mrb_alloc_class(mrb_state* mrb, RClass* super) {
  RClass* klass = (RClass*)tgc_alloc_opt(&mrb->gc, sizeof(RClass), 0, mrb_free_class);
  klass->super = super;
  klass->mt = kh_init(mt);

  return klass;
}

RClass* mrb_define_class(mrb_state* mrb, const char* name, RClass* super) {
  int ret;
  RClass* klass = mrb_alloc_class(mrb, super);

  khiter_t key = kh_put(ct, mrb->ct, name, &ret);
  kh_value(mrb->ct, key) = klass;

  return klass;
}

void mrb_free_object(void* ptr) {
  RObject* object = (RObject*)ptr;
  kh_destroy(iv, object->iv);
}

RObject* mrb_alloc_object(mrb_state* mrb, RClass* klass) {
  RObject* object = (RObject*)tgc_alloc_opt(&mrb->gc, sizeof(RObject), 0, mrb_free_object);
  object->c = klass;
  object->iv = kh_init(iv);

  return object;
}

mrb_value mrb_iv_set(mrb_value object, const char* name, mrb_value value) {
  if(IS_OBJECT_VALUE(object)) {
    int ret;
    RObject* obj = (RObject*)object.value.p;

    khiter_t key = kh_put(iv, obj->iv, name, &ret);
    kh_value(obj->iv, key) = value;

    return value;
  }

  return mrb_nil_value();
}

mrb_value mrb_iv_get(mrb_value object, const char* name) {
  if(IS_OBJECT_VALUE(object)) {
    RObject* obj = (RObject*)object.value.p;

    khiter_t key = kh_get(iv, obj->iv, name);
    if(key != kh_end(obj->iv)) {
      return kh_value(obj->iv, key);
    }
  }

  return mrb_nil_value();
}
