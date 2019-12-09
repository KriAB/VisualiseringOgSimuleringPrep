#include "newtonsmovementlaw.h"
#include "math_constants.h"

NewtonsMovementLaw::NewtonsMovementLaw()
{

}
void NewtonsMovementLaw::newtonsSecondLawAcceleration()
{
    // a = F+G*1/m //The goal
    // F = summen av alle kreftene altså = G + N
    // G = mg, altså massen * gravitasjons konstanten
    //N = |G| * n * cos alpha = [nx,ny,nz]*m*g* cos alpha
    // n = normalen på planet man er på.
    // Derfor må man regne normalen til den trekanten man er på.

    //Må ha kalkulert normal først!!!!! altså calcNormal()...
    //Ellers -> crash
    //
    acceleration = (calcNormalForce()-gravityForce)*(1/mass);
    //Den som var før, men den over virker mer rett for gravity går nedover her i negativ.
     //acceleration = (calcNormalForce()+gravityForce)*(1/mass);
}

gsl::Vector3D NewtonsMovementLaw::calcNormalForce()
{
    //Hvis Y er opp
    //  normalForce = normal*calcGravityForce().y * static_cast<float>(std::cos(alpha));//gsl::Vector3D().cross(normal,calcGravityForce())*static_cast<float>(std::cos (alpha));
    //Hvis z er opp
    normalForce = normal*calcGravityForce().z * static_cast<float>(std::cos(alpha));
    return normalForce;

    //normalForce = (v1-v0)x(v2-v0)
}

gsl::Vector3D NewtonsMovementLaw::calcGravityForce()
{
    //Hvis Y er opp
    //  gravityForce = gsl::Vector3D(0,/*-1**/(gsl::GRAVITY*mass),0); // TODO: Hva er opp i prosjektet?

    //Hvis Z er opp
    gravityForce = gsl::Vector3D(0,0,(gsl::GRAVITY*mass));

    return gravityForce;
}


gsl::Vector3D NewtonsMovementLaw::calcNormal3Pts(gsl::Vector3D p1, gsl::Vector3D p2, gsl::Vector3D p3)
{
    gsl::Vector3D v = p2-p1;
    gsl::Vector3D w = p3-p1;
    float Nx = (v.y*w.z)-(v.z*w.y);
    float Ny = (v.z*w.x)-(v.x*w.z);
    float Nz = (v.x*w.y)-(v.y*w.x);
    gsl::Vector3D temp(Nx, Ny, Nz);
    temp.normalize();
    normal = temp;

    return temp;
}
void NewtonsMovementLaw::calcAlpha()
{
    //n*k = cos alpha
    //Hvis Y er opp
//    alpha = std::acos(static_cast<double>(gsl::Vector3D().dot(normal,gsl::Vector3D(0,1,0))));
    //Hvis Z er opp
    alpha = std::acos(static_cast<double>(gsl::Vector3D().dot(normal,gsl::Vector3D(0,0,1))));
}


gsl::Vector3D NewtonsMovementLaw::calcNewVelocity(float deltaTime, gsl::Vector3D oldVelocity, gsl::Vector3D mAcceleration)
{
    // v = v0+a*t
    //v0 = oldVelocity
    return gsl::Vector3D(oldVelocity+(mAcceleration*deltaTime));
}

gsl::Vector3D NewtonsMovementLaw::getNormal() const
{
    return normal;
}

float NewtonsMovementLaw::calcHeight(gsl::Vector3D baryCoor, gsl::Vector3D p1, gsl::Vector3D p2, gsl::Vector3D p3)
{
    float temp;

    temp = (p1.y*baryCoor.x + p2.y *baryCoor.y + p3.y*baryCoor.z);

    return temp;
}
float NewtonsMovementLaw::getHeight() const
{
    return height;
}

gsl::Vector3D NewtonsMovementLaw::getAcceleration() const
{
    return acceleration;
}
