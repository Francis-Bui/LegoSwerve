typedef struct Vec2
{
    float x;
    float y;
    float magnitude;
} Vec2;

Vec2* Vec2_createVector(float xIn, float yIn);
float Vec2_dot(Vec2 *v1, Vec2 *v2);
void Vec2_scale(Vec2 *v, float scalar);
Vec2* Vec2_projectOnto(Vec2* v1, Vec2* v2);


Vec2* Vec2_createVector(float xIn, float yIn)
{
    Vec2 vec;
    vec.x = xIn;
    vec.y = yIn;
    vec.magnitude = sqrt(pow(vec.x,2) + pow(vec.y,2));
    return vec;
}

/**
 * Calculates the dot product of two vectors.
*/
float Vec2_dot(Vec2 *v1, Vec2* v2)
{
    return (v1 -> x)*(v2 -> x) + (v1 -> y)*(v2 -> y);
}

/**
 * Scales v and its magnitude by scalar
*/
void Vec2_scale(Vec2 *v, float scalar)
{
    v -> x *= scalar;
    v -> y *= scalar;
    v -> magnitude *= fabs(scalar);
}

/**
 * Returns a new vector of v1 projected onto v2
*/
Vec2* Vec2_projectOnto(Vec2* v1, Vec2* v2)
{
    //projects v1 onto v2
    float scalar = Vec2_dot(v1,v2) / pow(v2 -> magnitude, 2);

    Vec2 proj;
    proj.x = v2 -> x;
    proj.y = v2 -> y;
    proj.magnitude = v2 -> magnitude;
    Vec2_scale(&proj, scalar);
    return &proj;
}
