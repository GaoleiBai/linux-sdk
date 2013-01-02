#ifndef ICOMPARABLE_H
#define ICOMPARABLE_H

class NObject;

class IComparable {

public:
	IComparable();
	virtual ~IComparable();

	virtual int Compare(const NObject &o) = 0;
};

#endif // ICOMPARABLE_H
