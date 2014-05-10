#include <stdint.h>
#include <math.h>
#include "m3d.h"

v3 m4x4::apply(v3 p){

    m4x4 & m = *this;

    float x = m.a*p.x + m.b*p.y + m.c*p.z + m.d*p.w;
    float y = m.e*p.x + m.f*p.y + m.g*p.z + m.h*p.w;
    float z = m.i*p.x + m.j*p.y + m.k*p.z + m.l*p.w;
    float w = m.m*p.x + m.n*p.y + m.o*p.z + m.p*p.w;
    return v3(x,y,z,w);
  }

bool invertMatrix(const m4x4& m, m4x4& invOut)
{
    m4x4 inv;
    float det;

    inv.a = m.f  * m.k * m.p - 
             m.f  * m.l * m.o - 
             m.j  * m.g  * m.p + 
             m.j  * m.h  * m.o +
             m.n * m.g  * m.l - 
             m.n * m.h  * m.k;

    inv.e = -m.e  * m.k * m.p + 
              m.e  * m.l * m.o + 
              m.i  * m.g  * m.p - 
              m.i  * m.h  * m.o - 
              m.m * m.g  * m.l + 
              m.m * m.h  * m.k;

    inv.i = m.e  * m.j * m.p - 
             m.e  * m.l * m.n - 
             m.i  * m.f * m.p + 
             m.i  * m.h * m.n + 
             m.m * m.f * m.l - 
             m.m * m.h * m.j;

    inv.m = -m.e  * m.j * m.o + 
               m.e  * m.k * m.n +
               m.i  * m.f * m.o - 
               m.i  * m.g * m.n - 
               m.m * m.f * m.k + 
               m.m * m.g * m.j;

    inv.b = -m.b  * m.k * m.p + 
              m.b  * m.l * m.o + 
              m.j  * m.c * m.p - 
              m.j  * m.d * m.o - 
              m.n * m.c * m.l + 
              m.n * m.d * m.k;

    inv.f = m.a  * m.k * m.p - 
             m.a  * m.l * m.o - 
             m.i  * m.c * m.p + 
             m.i  * m.d * m.o + 
             m.m * m.c * m.l - 
             m.m * m.d * m.k;

    inv.g = -m.a  * m.j * m.p + 
              m.a  * m.l * m.n + 
              m.i  * m.b * m.p - 
              m.i  * m.d * m.n - 
              m.m * m.b * m.l + 
              m.m * m.d * m.j;

    inv.n = m.a  * m.j * m.o - 
              m.a  * m.k * m.n - 
              m.i  * m.b * m.o + 
              m.i  * m.c * m.n + 
              m.m * m.b * m.k - 
              m.m * m.c * m.j;

    inv.c = m.b  * m.g * m.p - 
             m.b  * m.h * m.o - 
             m.f  * m.c * m.p + 
             m.f  * m.d * m.o + 
             m.n * m.c * m.h - 
             m.n * m.d * m.g;

    inv.g = -m.a  * m.g * m.p + 
              m.a  * m.h * m.o + 
              m.e  * m.c * m.p - 
              m.e  * m.d * m.o - 
              m.m * m.c * m.h + 
              m.m * m.d * m.g;

    inv.k = m.a  * m.f * m.p - 
              m.a  * m.h * m.n - 
              m.e  * m.b * m.p + 
              m.e  * m.d * m.n + 
              m.m * m.b * m.h - 
              m.m * m.d * m.f;

    inv.o = -m.a  * m.f * m.o + 
               m.a  * m.g * m.n + 
               m.e  * m.b * m.o - 
               m.e  * m.c * m.n - 
               m.m * m.b * m.g + 
               m.m * m.c * m.f;

    inv.d = -m.b * m.g * m.l + 
              m.b * m.h * m.k + 
              m.f * m.c * m.l - 
              m.f * m.d * m.k - 
              m.j * m.c * m.h + 
              m.j * m.d * m.g;

    inv.h = m.a * m.g * m.l - 
             m.a * m.h * m.k - 
             m.e * m.c * m.l + 
             m.e * m.d * m.k + 
             m.i * m.c * m.h - 
             m.i * m.d * m.g;

    inv.l = -m.a * m.f * m.l + 
               m.a * m.h * m.j + 
               m.e * m.b * m.l - 
               m.e * m.d * m.j - 
               m.i * m.b * m.h + 
               m.i * m.d * m.f;

    inv.p = m.a * m.f * m.k - 
              m.a * m.g * m.j - 
              m.e * m.b * m.k + 
              m.e * m.c * m.j + 
              m.i * m.b * m.g - 
              m.i * m.c * m.f;

    det = m.a * inv.a + m.b * inv.e + m.c * inv.i + m.d * inv.m;

    if (det == 0)
        return false;

    det = 1.0 / det;

    invOut.a = inv.a * det;
    invOut.b = inv.b * det;
    invOut.c = inv.c * det;
    invOut.d = inv.d * det;
    invOut.e = inv.e * det;
    invOut.f = inv.f * det;
    invOut.g = inv.g * det;
    invOut.h = inv.h * det;
    invOut.i = inv.i * det;
    invOut.j = inv.j * det;
    invOut.k = inv.k * det;
    invOut.l = inv.l * det;
    invOut.m = inv.m * det;
    invOut.n = inv.n * det;
    invOut.o = inv.o * det;
    invOut.p = inv.p * det;

    return true;
}

m4x4 m4x4::inverse(){
  m4x4 m;
  invertMatrix(*this,m);
  return m;
}

v3 v3::right = v3(1,0,0,1);
v3 v3::up = v3(0,1,0,1);
v3 v3::forward = v3(0,0,1,1);
