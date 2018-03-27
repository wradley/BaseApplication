#pragma once
#include <string>
#include <map>
#include <tuple>
#include <functional>

namespace App
{
	typedef void* (*CpyFn) (void*);
	typedef void(*DelFn) (void*);

	class Object
	{
	public:

		Object();
		Object(const Object &o);
		Object(Object &&o);
		~Object();

		// custom setters
		void setbool(const std::string &key, bool val);
		void setint(const std::string &key, int val);
		void setunsignedint(const std::string &key, unsigned int val);
		void setfloat(const std::string &key, float val);
		void setdouble(const std::string &key, double val);
		void setstring(const std::string &key, const std::string &val);
		void setobject(const std::string &key, const Object &o);

		// custom getters
		bool getbool(const std::string &key);
		int getint(const std::string &key);
		unsigned int getunsignedint(const std::string &key);
		float getfloat(const std::string &key);
		double getdouble(const std::string &key);
		std::string getstring(const std::string &key);
		Object getobject(const std::string &key);

		void set(const std::string &key, void *value, CpyFn, DelFn);
		void* get(const std::string &key);

	private:

		struct Value
		{
			Value();
			Value(const Value &v);
			Value(Value &&v);
			~Value();

			void *val;
			CpyFn cpy;
			DelFn del;
		};

		std::map<std::string, Value> *_values;

	};
}
