
#include "Vector4.h"
#include "Point4.h"
#include "Matrix4.h"

void Vector4Test(void);
void Point4Test(void);
void Matrix4Test(void);

inline float randf(float a = 0.0f, float b = 1.0f) {
  return (((rand()&8191) * 0.0001220703125f)*(b-a))+a;
}

int main(void)
{
  srand(1024);

  Vector4Test();
  Point4Test();
  Matrix4Test();

  return 0;
}
void Matrix4Test(void)
{
  printf("Matrix4 Testing\n");

  printf("\n***** Matrix4(void) *****\n");
  Matrix4 mtx1;
  mtx1.Print();

  for(u32 i = 0; i < 16; ++i)
    mtx1.v[i] = randf(1.0f,2.0f);

  printf("\n***** Matrix4(const Matrix4& rhs) *****\n");
  mtx1.Print();
  Matrix4 mtx2(mtx1);
  mtx2.Print();

  printf("\n***** Matrix4(f32 mm00, f32 mm01, ... ) *****\n");
  Matrix4 mtx3(1.0f, 2.0f, 3.0f, 4.0f,
               5.0f, 6.0f, 7.0f, 8.0f,
               9.0f, 8.0f, 7.0f, 6.0f,
               5.0f, 4.0f, 3.0f, 2.0f);
  mtx3.Print();

  printf("\n***** operator=(const Matrix4& rhs) *****\n");
  mtx2.Print();
  mtx3 = mtx2;
  mtx3.Print();

  printf("\n***** operator*(const Vector4& rhs) *****\n");
  Vector4 vec1;
  mtx1.Print();
  vec1.Print();
  vec1 = mtx1 * vec1;
  vec1.Print();
  vec1 = Vector4(1.0f,2.0f,3.0f,4.0f);
  vec1.Print();
  vec1 = mtx1 * vec1;
  vec1.Print();

  printf("\n***** operator*(const Point4& rhs) *****\n");

  Point4 pnt1;
  mtx1.Print();
  pnt1.Print();
  pnt1 = mtx1 * pnt1;
  pnt1.Print();
  pnt1 = Point4(1.0f,2.0f,3.0f,4.0f);
  pnt1.Print();
  pnt1 = mtx1 * pnt1;
  pnt1.Print();

  printf("\n***** operator+(const Matrix4& rhs) *****\n");
  (mtx1 + mtx2).Print();

  printf("\n***** operator-(const Matrix4& rhs) *****\n");
  (mtx1 - mtx2).Print();

  printf("\n***** operator*(const Matrix4& rhs) *****\n");
  (mtx1 * mtx2).Print();

  printf("\n***** operator+=(const Matrix4& rhs) *****\n");
  mtx1 += mtx2;
  mtx1.Print();

  printf("\n***** operator-=(const Matrix4& rhs) *****\n");
  mtx1 -= mtx2;
  mtx1.Print();

  printf("\n***** operator*=(const Matrix4& rhs) *****\n");
  mtx1 *= mtx2;
  mtx1.Print();

  printf("\n***** operator*(const f32 rhs) *****\n");
  (mtx1 * 3.0f).Print();

  printf("\n***** operator/(const f32 rhs) *****\n");
  (mtx1 / 3.0f).Print();

  printf("\n***** operator*=(const f32 rhs) *****\n");
  mtx1 *= 3.0f;
  mtx1.Print();

  printf("\n***** operator/=(const f32 rhs) *****\n");
  mtx1 /= 2.0f;
  mtx1.Print();

  printf("\n***** operator==(const Matrix4& rhs) *****\n");
  mtx1 = mtx2;
  mtx1.Print();
  mtx2.Print();

  printf("\nShould be Equal: ");
  if(mtx1 == mtx2)
    printf("Success\n");
  else
    printf("Failure\n");

  printf("\nAssigning mtx2 to mtx1\n");
  mtx1 = mtx2;
  mtx1.Print();
  mtx2.Print();
  printf("\nModifying X Component from %f ",mtx1.v[0]);
  mtx1.v[0] -= 0.00005f;
  printf("to %f\n\n",mtx1.v[0]);
  mtx1.Print();
  mtx2.Print();

  printf("\nShould be Equal: ");
  if(mtx1 == mtx2)
    printf("Success\n");
  else
    printf("Failure\n");

  printf("\n***** operator!=(const Matrix4& rhs) *****\n");
  mtx1 = mtx3;
  mtx1.Print();
  mtx2.Print();

  printf("\nShould not be Equal: ");
  if(mtx1 != mtx2)
    printf("Success\n");
  else
    printf("Failure\n");

  printf("\nAssigning mtx2 to mtx1\n");
  mtx1 = mtx2;
  mtx1.Print();
  mtx2.Print();
  printf("\nModifying 1st Component from %f ",mtx1.v[0]);
  mtx1.v[0] += 0.001f;
  printf("to %f\n\n",mtx1.v[0]);
  mtx1.Print();
  mtx2.Print();

  printf("\nShould not be Equal: ");
  if(mtx1 != mtx2)
    printf("Success\n");
  else
    printf("Failure\n");

  printf("\n***** Zero(void) *****\n");
  for(u32 i = 0; i < 16; ++i)
    mtx1.v[i] = randf(1.0f,5.0f);
  mtx1.Print();
  mtx1.Zero();
  mtx1.Print();

  printf("\n***** Identity(void) *****\n");
  for(u32 i = 0; i < 16; ++i)
    mtx1.v[i] = randf(1.0f,5.0f);
  mtx1.Print();
  mtx1.Identity();
  mtx1.Print();
}
void Point4Test(void)
{
  printf("Point4 Testing\n");

  printf("\n***** Point4(void) *****\n");
  Point4 pnt1;
  pnt1.Print();

  for(u32 i = 0; i < 4; ++i)
    pnt1.v[i] = randf(1.0f,2.0f);

  printf("\n***** Point4(const Point4& rhs) *****\n");
  pnt1.Print();
  Point4 pnt2(pnt1);
  pnt2.Print();

  printf("\n***** Point4(f32 xx, f32 yy, f32 zz, f32 ww) *****\n");
  Point4 pnt3(1.0f,2.0f,3.0f);
  pnt3.Print();
  Point4 pnt4(1.0f,2.0f,3.0f,4.0f);
  pnt4.Print();

  for(u32 i = 0; i < 4; ++i)
    pnt2.v[i] = randf(1.0f,2.0f);

  printf("\n***** operator=(const Point4& rhs) *****\n");
  pnt2.Print();
  pnt1 = pnt2;
  pnt1.Print();

  printf("\n***** operator-(void) *****\n");
  (-pnt1).Print();

  for(u32 i = 0; i < 4; ++i)
    pnt2.v[i] = randf(1.0f,5.0f);

  printf("\n***** operator-(const Point4& rhs) *****\n");
  Vector4 vec1 = pnt1 - pnt2;
  vec1.Print();

  for(u32 i = 0; i < 4; ++i)
    vec1.v[i] = randf(1.0f,5.0f);

  printf("\n***** operator+(const Vector4& rhs) *****\n");
  pnt1.Print();
  vec1.Print();
  (pnt1 + vec1).Print();

  printf("\n***** operator-(const Vector4& rhs) *****\n");
  pnt1.Print();
  vec1.Print();
  (pnt1 - vec1).Print();

  printf("\n***** operator+=(const Vector4& rhs) *****\n");
  pnt1.Print();
  vec1.Print();
  pnt1 += vec1;
  pnt1.Print();

  printf("\n***** operator-=(const Vector4& rhs) *****\n");
  pnt1.Print();
  vec1.Print();
  pnt1 -= vec1;
  pnt1.Print();

  pnt1 = pnt2;

  printf("\nShould be Equal: ");
  if(pnt1 == pnt2)
    printf("Success\n");
  else
    printf("Failure\n");

  printf("\nAssigning pnt2 to pnt1\n");
  pnt1 = pnt2;
  pnt1.Print();
  pnt2.Print();
  printf("\nModifying X Component from %f ",pnt1.x);
  pnt1.x -= 0.00005f;
  printf("to %f\n\n",pnt1.x);
  pnt1.Print();
  pnt2.Print();

  printf("\nShould be Equal: ");
  if(pnt1 == pnt2)
    printf("Success\n");
  else
    printf("Failure\n");

  printf("\n***** operator!=(const Point4& rhs) *****\n");
  pnt1 = pnt3;
  pnt1.Print();
  pnt2.Print();

  printf("\nShould not be Equal: ");
  if(pnt1 != pnt2)
    printf("Success\n");
  else
    printf("Failure\n");

  printf("\nAssigning pnt2 to pnt1\n");
  pnt1 = pnt2;
  pnt1.Print();
  pnt2.Print();
  printf("\nModifying X Component from %f ",pnt1.x);
  pnt1.x += 0.001f;
  printf("to %f\n\n",pnt1.x);
  pnt1.Print();
  pnt2.Print();

  printf("\nShould not be Equal: ");
  if(pnt1 != pnt2)
    printf("Success\n");
  else
    printf("Failure\n");

  Point4 pnt5;

  for(u32 i = 0; i < 4; ++i)
    pnt5.v[i] = randf(1.0f,5.0f);

  printf("\n***** Zero(void) *****\n\n");
  pnt5.Print();
  pnt5.Zero();
  pnt5.Print();
}

void Vector4Test(void)
{
  printf("Vector4 Testing\n");

  printf("\n***** Vector4(void) *****\n");
  Vector4 vec1;
  vec1.Print();

  for(u32 i = 0; i < 4; ++i)
    vec1.v[i] = randf(1.0f,2.0f);

  printf("\n***** Vector4(const Vector4& rhs) *****\n");
  vec1.Print();
  Vector4 vec2(vec1);
  vec2.Print();

  printf("\n***** Vector4(f32 xx, f32 yy, f32 zz, f32 ww) *****\n");
  Vector4 vec3(1.0f,2.0f,3.0f);
  vec3.Print();
  Vector4 vec4(1.0f,2.0f,3.0f,4.0f);
  vec4.Print();

  for(u32 i = 0; i < 4; ++i)
    vec2.v[i] = randf(1.0f,2.0f);

  printf("\n***** operator=(const Vector4& rhs) *****\n");
  vec2.Print();
  vec1 = vec2;
  vec1.Print();

  printf("\n***** operator-(void) *****\n");
  (-vec1).Print();

  printf("\n***** operator+(const Vector4& rhs) *****\n");
  (vec1 + vec4).Print();

  printf("\n***** operator-(const Vector4& rhs) *****\n");
  (vec1 - vec4).Print();

  printf("\n***** operator*(const f32 rhs) *****\n");
  (vec1 * 3.0f).Print();

  printf("\n***** operator/(const f32 rhs) *****\n");
  (vec1 / 2.0f).Print();

  printf("\n***** operator+=(const Vector4& rhs) *****\n");
  vec1.Print();
  vec1 += vec4;
  vec1.Print();

  printf("\n***** operator-=(const Vector4& rhs) *****\n");
  vec1.Print();
  vec1 -= vec4;
  vec1.Print();

  printf("\n***** operator*=(const f32 rhs) *****\n");
  vec1.Print();
  vec1 *= 3.0f;
  vec1.Print();

  printf("\n***** operator/=(const f32 rhs) *****\n");
  vec1.Print();
  vec1 /= 2.0f;
  vec1.Print();

  printf("\n***** operator==(const Vector4& rhs) *****\n");
  vec1 = vec2;
  vec1.Print();
  vec2.Print();

  printf("\nShould be Equal: ");
  if(vec1 == vec2)
    printf("Success\n");
  else
    printf("Failure\n");

  printf("\nAssigning vec2 to vec1\n");
  vec1 = vec2;
  vec1.Print();
  vec2.Print();
  printf("\nModifying X Component from %f ",vec1.x);
  vec1.x -= 0.00005f;
  printf("to %f\n\n",vec1.x);
  vec1.Print();
  vec2.Print();

  printf("\nShould be Equal: ");
  if(vec1 == vec2)
    printf("Success\n");
  else
    printf("Failure\n");

  printf("\n***** operator!=(const Vector4& rhs) *****\n");
  vec1 = vec3;
  vec1.Print();
  vec2.Print();

  printf("\nShould not be Equal: ");
  if(vec1 != vec2)
    printf("Success\n");
  else
    printf("Failure\n");

  printf("\nAssigning vec2 to vec1\n");
  vec1 = vec2;
  vec1.Print();
  vec2.Print();
  printf("\nModifying X Component from %f ",vec1.x);
  vec1.x += 0.001f;
  printf("to %f\n\n",vec1.x);
  vec1.Print();
  vec2.Print();

  printf("\nShould not be Equal: ");
  if(vec1 != vec2)
    printf("Success\n");
  else
    printf("Failure\n");

  for(u32 i = 0; i < 4; ++i) {
    vec1.v[i] = randf(1.0f,2.0f);
    vec2.v[i] = randf(2.0f,3.0f);
    vec3.v[i] = randf(3.0f,4.0f);
    vec4.v[i] = randf(4.0f,5.0f);
  }

  printf("\n***** Dot(const Vector4& rhs) *****\n\n");
  printf("vec1.Dot(vec2) returns %5.3f\n", vec1.Dot(vec2));
  printf("vec2.Dot(vec1) returns %5.3f\n", vec2.Dot(vec1));
  printf("vec3.Dot(vec2) returns %5.3f\n", vec3.Dot(vec2));
  printf("vec4.Dot(vec1) returns %5.3f\n", vec4.Dot(vec1));

  printf("\n***** Cross(const Vector4& rhs) *****\n");
  printf("\nvec1.Cross(vec2)\n");
  (vec1.Cross(vec2)).Print();
  printf("\nvec2.Cross(vec1)\n");
  (vec2.Cross(vec1)).Print();
  printf("\nvec3.Cross(vec4)\n");
  (vec3.Cross(vec4)).Print();
  printf("\nvec2.Cross(vec3)\n");
  (vec2.Cross(vec3)).Print();

  printf("\n***** Length(void) *****\n\n");
  printf("vec1.Length() returns %5.3f\n", vec1.Length());
  printf("vec2.Length() returns %5.3f\n", vec2.Length());
  printf("vec3.Length() returns %5.3f\n", vec3.Length());
  printf("vec4.Length() returns %5.3f\n", vec4.Length());

  printf("\n***** LengthSq(void) *****\n\n");
  printf("vec1.LengthSq() returns %5.3f\n", vec1.LengthSq());
  printf("vec2.LengthSq() returns %5.3f\n", vec2.LengthSq());
  printf("vec3.LengthSq() returns %5.3f\n", vec3.LengthSq());
  printf("vec4.LengthSq() returns %5.3f\n", vec4.LengthSq());

  printf("\n***** Normalize(void) *****\n");
  printf("\nNormalizing Zero Vector\n");
  Vector4 vec5;
  vec5.Print();
  vec5.Normalize();
  vec5.Print();
  printf("\nFilling Random Values\n");
  for(u32 i = 0; i < 4; ++i)
    vec5.v[i] = randf(1.0f,5.0f);
  vec5.Print();
  printf("\nvec5.Length() returns %5.3f\n", vec5.Length());
  printf("Normalizing Non-Zero Vector\n");
  vec5.Normalize();
  printf("vec5.Length() returns %5.3f\n", vec5.Length());

  printf("\n***** Zero(void) *****\n\n");
  vec5.Print();
  vec5.Zero();
  vec5.Print();
}