#include "Object.h"

App::Object::Object() : _values(new std::map<std::string, Value>)
{}


App::Object::Object(const Object &o) : _values(new std::map<std::string, Value>(*o._values))
{}


App::Object::Object(Object &&o) : _values(o._values)
{
	o._values = nullptr;
}


App::Object::~Object()
{
	if (_values) delete _values;
}


void App::Object::setbool(const std::string & key, bool val)
{
	set(key, &val, [](void *b)
	{
		return (void*)new bool(*((bool*)b));
	}, [](void *b) 
	{
		delete (bool*)b;
	});
}


void App::Object::setint(const std::string & key, int val)
{
	set(key, &val, [](void *b)
	{
		return (void*)new int(*((int*)b));
	}, [](void *b)
	{
		delete (int*)b;
	});
}


void App::Object::setunsignedint(const std::string & key, unsigned int val)
{
	set(key, &val, [](void *b)
	{
		return (void*)new unsigned int(*((unsigned int*)b));
	}, [](void *b)
	{
		delete (unsigned int*)b;
	});
}


void App::Object::setfloat(const std::string & key, float val)
{
	set(key, &val, [](void *b)
	{
		return (void*)new float(*((float*)b));
	}, [](void *b)
	{
		delete (float*)b;
	});
}


void App::Object::setdouble(const std::string & key, double val)
{
	set(key, &val, [](void *b)
	{
		return (void*)new double(*((double*)b));
	}, [](void *b)
	{
		delete (double*)b;
	});
}


void App::Object::setstring(const std::string & key, const std::string & val)
{
	set(key, (void*)&val, [](void *b)
	{
		return (void*)new std::string(*((std::string*)b));
	}, [](void *b)
	{
		delete (std::string*)b;
	});
}

void App::Object::setobject(const std::string & key, const Object & o)
{
	set(key, (void*)&o, [](void *b)
	{
		return (void*)new Object(*((Object*)b));
	}, [](void *b)
	{
		delete (Object*)b;
	});
}


bool App::Object::getbool(const std::string & key)
{
	if (_values->find(key) != _values->end())
		return *((bool*)(_values->operator[](key).val));
	return false;
}


int App::Object::getint(const std::string & key)
{
	if (_values->find(key) != _values->end())
		return *((int*)(_values->operator[](key).val));
	return 0;
}


unsigned int App::Object::getunsignedint(const std::string & key)
{
	if (_values->find(key) != _values->end())
		return *((unsigned int*)(_values->operator[](key).val));
	return 0;
}


float App::Object::getfloat(const std::string & key)
{
	if (_values->find(key) != _values->end())
		return *((float*)(_values->operator[](key).val));
	return 0.0f;
}


double App::Object::getdouble(const std::string & key)
{
	if (_values->find(key) != _values->end())
		return *((double*)(_values->operator[](key).val));
	return 0.0;
}


std::string App::Object::getstring(const std::string & key)
{
	if (_values->find(key) != _values->end())
		return *((std::string*)(_values->operator[](key).val));
	return std::string();
}


App::Object App::Object::getobject(const std::string & key)
{
	if (_values->find(key) != _values->end())
		return *((Object*)(_values->operator[](key).val));
	return Object();
}


void App::Object::set(const std::string &key, void *value, CpyFn c, DelFn d)
{
	// if there was an old value, delete it
	if (_values->find(key) != _values->end())
		_values->operator[](key).del(_values->operator[](key).val);

	// store the new one
	_values->operator[](key).cpy = c;
	_values->operator[](key).del = d;
	_values->operator[](key).val = c(value);
}


void* App::Object::get(const std::string &key)
{
	if (_values->find(key) != _values->end())
	{
		return _values->operator[](key).val;
	}

	return (void*)nullptr;
}


App::Object::Value::Value() : val(nullptr)
{}


App::Object::Value::Value(const Value &v) : val(nullptr), cpy(v.cpy), del(v.del)
{
	val = cpy(v.val);
}


App::Object::Value::Value(Value &&v) : val(v.val), cpy(v.cpy), del(v.del)
{
	v.val = nullptr;
}


App::Object::Value::~Value()
{
	if (val)
	{
		del(val);
	}
}