void cross(float *a, float *b, float *r) {
    r[0]=a[1]*b[2]-a[2]*b[1];
    r[1]=a[2]*b[0]-a[0]*b[2];
    r[2]=a[0]*b[1]-a[1]*b[0];
}

void dot(float *a, float *b, float *r) {
    *r=a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}

void sub(float *a, float *b, float *r) {
    r[0]=a[0]-b[0];
    r[1]=a[1]-b[1];
    r[2]=a[2]-b[2];
}