#include "Mat4.h"

Mat4::Mat4(float i)
{
    memset(val, 0, sizeof(val));
    val[0][0] = i;
    val[1][1] = i;
    val[2][2] = i;
    val[3][3] = i;
}

Mat4 Mat4::operator*(Mat4& b)
{
    Mat4 temp(0);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                temp.val[j][i] += val[k][i] * b.val[j][k];
            }
        }
    }
    return temp;
}

void Mat4::translate(Vector3 v)
{
    Mat4 transMat;
    Vector3 m0(val[0]);
    Vector3 m1(val[1]);
    Vector3 m2(val[2]);
    Vector3 t = m0 * v.x + m1 * v.y + m2 * v.z;
    val[3][0] += t.x; val[3][1] += t.y; val[3][2] += t.z;
}

void Mat4::rotate(float angle, Vector3 u)
{
    if (u.module() == 0) return;
    Vector3 eulerAngle = 0.5f * angle * u.normalize();
    float cx = cos(eulerAngle.x);
    float cy = cos(eulerAngle.y);
    float cz = cos(eulerAngle.z);
    float sx = sin(eulerAngle.x);
    float sy = sin(eulerAngle.y);
    float sz = sin(eulerAngle.z);
    Vector4 quaternion;
    quaternion.w = cx * cy * cz + sx * sy * sz;
    quaternion.x = cy * cz * sx - cx * sy * sz;
    quaternion.y = cx * cz * sy + cy * sx * sz;
    quaternion.z = cx * cy * sz - cz * sx * sy;

    float qxx = quaternion.x * quaternion.x;
    float qyy = quaternion.y * quaternion.y;
    float qzz = quaternion.z * quaternion.z;
    float qxy = quaternion.x * quaternion.y;
    float qxz = quaternion.x * quaternion.z;
    float qyz = quaternion.y * quaternion.z;
    float qwx = quaternion.w * quaternion.x;
    float qwy = quaternion.w * quaternion.y;
    float qwz = quaternion.w * quaternion.z;

    Mat4 r(1);
    r.val[0][0] = 1.0f - 2.0f * (qyy + qzz);
    r.val[0][1] = 2.0f * (qxy + qwz);
    r.val[0][2] = 2.0f * (qxz - qwy);

    r.val[1][0] = 2.0f * (qxy - qwz);
    r.val[1][1] = 1.0f - 2.0f * (qxx + qzz);
    r.val[1][2] = 2.0f * (qyz + qwx);

    r.val[2][0] = 2.0f * (qxz + qwy);
    r.val[2][1] = 2.0f * (qyz - qwx);
    r.val[2][2] = 1.0f - 2.0f * (qxx + qyy);

    *this = (*this) * r;
    /*float costheta = cos(angle);
    float sintheta = sin(angle);
    u.normalize();
    Vector3 temp((1 - costheta) * u);

    Mat4 r(0);
    r.val[0][0] = costheta + temp.x * u.x;
    r.val[0][1] = temp.x * u.y + sintheta * u.z;
    r.val[0][2] = temp.x * u.z - sintheta * u.y;

    r.val[1][0] = temp.y * u.x - sintheta * u.z;
    r.val[1][1] = costheta + temp.y * u.y; 
    r.val[1][2] = temp.y * u.z + sintheta * u.x;

    r.val[2][0] = temp.z * u.x + sintheta * u.y;
    r.val[2][1] = temp.z * u.y - sintheta * u.x;
    r.val[2][2] = costheta + temp.z * u.z;

    Vector3 m0(val[0]);
    Vector3 m1(val[1]);
    Vector3 m2(val[2]);
    Vector3 r0 = m0 * r.val[0][0] + m1 * r.val[0][1] + m2 * r.val[0][2];
    Vector3 r1 = m0 * r.val[1][0] + m1 * r.val[1][1] + m2 * r.val[1][2];
    Vector3 r2 = m0 * r.val[2][0] + m1 * r.val[2][1] + m2 * r.val[2][2];
    val[0][0] = r0.x; val[0][1] = r0.y; val[0][2] = r0.z;
    val[1][0] = r1.x; val[1][1] = r1.y; val[1][2] = r1.z;
    val[2][0] = r2.x; val[2][1] = r2.y; val[2][2] = r2.z;*/
}

void Mat4::scale(Vector3 s)
{
    Vector3 m0(val[0]);
    Vector3 m1(val[1]);
    Vector3 m2(val[2]);
    Vector3 r0 = m0 * s.x;
    Vector3 r1 = m1 * s.y;
    Vector3 r2 = m2 * s.z;
    val[0][0] = r0.x; val[0][1] = r0.y; val[0][2] = r0.z;
    val[1][0] = r1.x; val[1][1] = r1.y; val[1][2] = r1.z;
    val[2][0] = r2.x; val[2][1] = r2.y; val[2][2] = r2.z;
}

Mat4 perspective(float fovy, float aspect, float zNear, float zFar)
{
    float tanHalfFovy = tan(fovy / 2.0f);
    Mat4 res(0);
    res.val[0][0] = 1.0f / (aspect * tanHalfFovy);
    res.val[1][1] = 1.0f / tanHalfFovy;
    res.val[2][2] = -(zFar + zNear) / (zFar - zNear);
    res.val[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
    res.val[2][3] = -1.0f;
    return res;
}

Mat4 lookAtRH(const Vector3& eye, const Vector3& center, const Vector3& up)
{
    Vector3 f((center - eye).normalize());
    Vector3 s(f.cross(up).normalize());
    Vector3 u(s.cross(f));
    Mat4 res;
    res.val[0][0] = s.x;
    res.val[1][0] = s.y;
    res.val[2][0] = s.z;
    res.val[3][0] = -s.dot(eye);
    res.val[0][1] = u.x;
    res.val[1][1] = u.y;
    res.val[2][1] = u.z;
    res.val[3][1] = -u.dot(eye);
    res.val[0][2] = -f.x;
    res.val[1][2] = -f.y;
    res.val[2][2] = -f.z;
    res.val[3][2] = f.dot(eye);
    return res;
}
