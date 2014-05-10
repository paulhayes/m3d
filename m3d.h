#ifndef m3d_h
#define m3d_h

struct v3 {
	static v3 forward;
	static v3 up;
	static v3 right;

	float x;
	float y;
	float z;
	float w;

	v3(float x,float y,float z){
		v3(x,y,z,1);
	}

	v3(float x,float y,float z,float w){
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	v3(){
		x = 0;
		y = 0;
		z = 0;
		w = 1;
	}

	v3 operator +(const v3& p) const{
		return v3(x+p.x,y+p.y,z+p.z,1);
	}

	v3 operator -(const v3& p) const{
		return v3(x-p.x,y-p.y,z-p.z,1);
	}

	float operator *(const v3& p) const{
		return x*p.x+y*p.y+z*p.z;
	}

	v3 operator *(float s) const{
		return v3(s*x,s*y,s*z,1);
	}

	static v3 cross(const v3& a, const v3& b) {
		v3 c = v3();
		
		c.x = a.y * b.z - a.z * b.y;
		c.y = a.z * b.x - a.x * b.z;
		c.z = a.x * b.y - a.y * b.x; 
		
 		return c;
	}

	float length(){
		return sqrt( (x*x)+(y*y)+(z*z) );
	}

	v3 normalize(){
		float d = length();
		if( d == 0 ) return v3();
		return v3(x/d,y/d,z/d,1);
	}

	v3 project(const v3& p){
		v3 s = this->normalize();
		v3 o = s * ( p * s );

		return o;
	}

	v3 orthoganal(const v3& p){
		v3 s = this->project(p);
		v3 o = p - s;
		return o;
	}


};

struct m4x4{
	float a; float b; float c; float d;
	float e; float f; float g; float h;
	float i; float j; float k; float l;
	float m; float n; float o; float p;

	m4x4(){
		this->a=1;
		this->f=1;
		this->k=1;
		this->p=1;

		this->b=this->c=this->d=0;
		this->e=this->g=this->h=0;
		this->i=this->j=this->l=0;
		this->m=this->n=this->o=0;
	}

	m4x4 operator *(const m4x4& m2){
		m4x4& m1 = *this;
		m4x4 o;

		o.a = m1.a * m2.a + m1.b * m2.e + m1.c * m2.i + m1.d * m2.m;
		o.b = m1.a * m2.b + m1.b * m2.f + m1.c * m2.j + m1.d * m2.n;
		o.c = m1.a * m2.c + m1.b * m2.g + m1.c * m2.k + m1.d * m2.o;
		o.d = m1.a * m2.d + m1.b * m2.h + m1.c * m2.l + m1.d * m2.p;

		o.e = m1.e * m2.a + m1.f * m2.e + m1.g * m2.i + m1.h * m2.m;
		o.f = m1.e * m2.b + m1.f * m2.f + m1.g * m2.j + m1.h * m2.n;
		o.g = m1.e * m2.c + m1.f * m2.g + m1.g * m2.k + m1.h * m2.o;
		o.h = m1.e * m2.d + m1.f * m2.h + m1.g * m2.l + m1.h * m2.p;

		o.i = m1.i * m2.a + m1.j * m2.e + m1.k * m2.i + m1.l * m2.m;
		o.j = m1.i * m2.b + m1.j * m2.f + m1.k * m2.j + m1.l * m2.n;
		o.k = m1.i * m2.c + m1.j * m2.g + m1.k * m2.k + m1.l * m2.o;
		o.l = m1.i * m2.d + m1.j * m2.h + m1.k * m2.l + m1.l * m2.p;

		o.m = m1.m * m2.a + m1.n * m2.e + m1.o * m2.i + m1.p * m2.m;
		o.n = m1.m * m2.b + m1.n * m2.f + m1.o * m2.j + m1.p * m2.n;
		o.o = m1.m * m2.c + m1.n * m2.g + m1.o * m2.k + m1.p * m2.o;
		o.p = m1.m * m2.d + m1.n * m2.h + m1.o * m2.l + m1.p * m2.p;

		return o;
	}

	m4x4 operator *(float s){
		m4x4 m = *this;
		m.a *= s;
		m.b *= s;
		m.c *= s;
		m.d *= s;

		m.e *= s;
		m.f *= s;
		m.g *= s;
		m.h *= s;

		m.i *= s;
		m.j *= s;
		m.k *= s;
		m.l *= s;

		m.m *= s;
		m.n *= s;
		m.o *= s;
		m.p *= s;

		return m;
 	}

	m4x4 translate(const v3& p){
		m4x4 m;
		m.d = p.x;
		m.h = p.y;
		m.l = p.z;
		m.p = p.w;
		return (*this)*m;
	}

	m4x4 rotation(const v3& dir, const v3& up){
		v3 right = v3::cross(dir,up);
		m4x4 m;
		m.a = right.x;
		m.b = up.x;
		m.c = dir.x;
		m.d = 0;
		m.e = right.y;
		m.f = up.y;
		m.g = dir.y;
		m.h = 0;
		m.i = right.z;          
		m.j = up.z;
		m.k = dir.z;
		m.l = 0;
		m.m = 0;
		m.n = 0;
		m.o = 0;
		m.p = 1;
		return *this*m;
	}

	m4x4 scale(float a){
		return *this*a;
	}

	m4x4 inverse();

	v3 apply(v3 p);


};

struct point {
	v3 position;
	uint32_t colour;

	point(float x,float y,float z){
		point(x,y,z,1);
	}
	
	point(float x,float y,float z, float w){
		this->position.x = x;
		this->position.y = y;
		this->position.z = z;
		this->position.w = w;
	}

	

};

struct line {
	v3 start;
	v3 end;

	uint32_t colour;
};

struct camera {
	float f;
	float width;
	float height;
	
	v3 project(const v3 point){
		v3 p;
		if( point.z > 0 ){
			p.x = f/point.z * point.x + 0.5 * width;
			p.y = f/point.z * point.y + 0.5 * height;
		}
		p.z = ( point.z > 0 ) ? 1 : 0;
		return p;
	}
};

#endif