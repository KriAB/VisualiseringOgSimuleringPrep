#ifndef NEWTONSMOVEMENTLAW_H
#define NEWTONSMOVEMENTLAW_H
#include "vector3d.h"
#include "vector2d.h"

class NewtonsMovementLaw
{
public:
    //F = ma
    //a= F/m
    NewtonsMovementLaw();
    void newtonsSecondLawAcceleration();
    gsl::Vector3D calcNormalForce();
    gsl::Vector3D calcGravityForce();
    gsl::Vector3D calcNormal3Pts(gsl::Vector3D p1, gsl::Vector3D p2, gsl::Vector3D p3);
    void calcAlpha();
    float calcHeight(gsl::Vector3D baryCoor, gsl::Vector3D p1, gsl::Vector3D p2, gsl::Vector3D p3);
    float getHeight() const;
    gsl::Vector3D getAcceleration() const;

    gsl::Vector3D calcNewVelocity(float deltaTime, gsl::Vector3D oldVelocity, gsl::Vector3D mAcceleration);

    gsl::Vector3D getNormal() const;

private:
    float height = 1;

    gsl::Vector3D acceleration;
    gsl::Vector3D gravityForce; //force
    float mass = 1;
    gsl::Vector3D normal; //normalen i kontaktpunktet med underlaget
    gsl::Vector3D normalForce;
    double alpha;

};

#endif // NEWTONSMOVEMENTLAW_H
