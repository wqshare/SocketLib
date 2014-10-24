#ifndef UNCOPYABLE_h_
#define UNCOPYABLE_h_

class uncopyable
{
protected:
	uncopyable() {}
	~uncopyable() {}
private:
	uncopyable(const uncopyable &);
	const uncopyable & operator== (const uncopyable &);
};


#endif // UNCOPYABLE_h_
