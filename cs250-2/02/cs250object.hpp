#ifndef OBJECT_H
#define OBJECT_H

struct Object
{
	virtual ~Object(void) {};
	virtual int VertexCount(void) const = 0;
	virtual const Point& GetVertex(int i) const = 0;
	
	struct Edge
	{
		int begin;
		int end;
	};
	
	virtual int EdgeCount(void) const = 0;
	virtual const Edge& GetEdge(int i) const = 0;
};

class Cube : public Object
{
	public:
		Cube(void);
		~Cube(void);
		
		int VertexCount(void) const;
		const Point& GetVertex(int i) const;
		int EdgeCount(void) const;
		const Edge& GetEdge(int i) const;
};

class Sphere : public Object
{
	public:
		Sphere(int m, int n);
		~Sphere(void);
		
		int VertexCount(void) const;
		const Point& GetVertex(int i) const;
		int EdgeCount(void) const;
		const Edge& GetEdge(int i) const;
};

#endif // OBJECT_H
