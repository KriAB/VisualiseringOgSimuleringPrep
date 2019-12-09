#include <iostream>
#include "newtonsmovementlaw.h"
#include "vector3d.h"
#include <array>
#include <vector>
#include <cmath>

using namespace std;

struct Grid
{
    gsl::Vector3D mGrid[4][3];

    // R  |--- Kolonne 3
    // a  |
    // d  |
    // 4  |
    //-----------
    // 4 x 3 matrise
    //----------
    //   j  j   j
    //i  0  1   2
    //i  3  4   5
    //i  6  7   8
    //i  9  10  11
    float minX;
    float minY;
    void setMat(std::vector<gsl::Vector3D> points)
    {
        // finne min x og min y
        minXY(points);

        for(int i= 0; i < 4; ++i )
        {
            for (int j = 0; j <3; ++j)
            {
                //Må sjekke hvor mange punkter som faller innenfor samme spot.
                //Hvis det er flere må man + dem på og dele på antall punkter senere for å finne et gjenomsnitt.
                int pointCount = 0;
                for(auto pts : points)
                {
                    mGrid[i][j].x = minX+2*i;
                    mGrid[i][j].y = minY+2*j;
                    if( minX + 2*i - 1 <= pts.x && pts.x < minX + 2*i +1)
                    {
                        if(minY + 2 * j - 1 <= pts.y && pts.y < minY +2*j +1)
                        {

                            mGrid[i][j].z = mGrid[i][j].z + pts.z;
                            pointCount++;
                        }
                    }
                }

                if(pointCount != 0)
                {
                    mGrid[i][j] = gsl::Vector3D(mGrid[i][j].x, mGrid[i][j].y, mGrid[i][j].z/pointCount );
                }
            }
        }
    }
    bool compare(float a, float b)
    {
        double epsilon = 0.00001;
        //sjekke om ax er mindre en bx
        if(a < b ||(fabs (static_cast<double>(a-b)) < static_cast<double>(a)* epsilon))
            return true;

        return false;
    }

    void minXY(std::vector<gsl::Vector3D> points)
    {
        minX = points.at(0).x;
        minY = points.at(0).y;
        for(int i = 1; i< points.size(); i++)
        {
            if(!compare(minX, points.at(i).x))
            {
                minX = points.at(i).x;
            }
            if(!compare(minY, points.at(i).y))
            {
                minY = points.at(i).y;
            }
        }
    }
    void print(int num)
    {
        for(int i = 0; i< 4 ; ++i)
        {
            for(int j = 0; j <3 ; ++j)
            {
                if(num == 0)
                    std::cout << mGrid[i][j] << "  |  ";
                if(num == 1)
                    std::cout << " Z: " << mGrid[i][j].z << "  |  ";

                if(num == 2)
                    std::cout <<" | " << " X: " << mGrid[i][j].x << " Y: " <<  mGrid[i][j].y <<"  |  ";
            }
            std::cout << std::endl;
        }
    }
    std::vector<gsl::Vector3D> triangulate()
    {
        std::vector<gsl::Vector3D> temp;

        for(int i =0; i < 4-1; ++i)
        {
            for (int j = 0; j < 3-1; ++j)
            {

                temp.push_back(mGrid[i][j]);
                temp.push_back(mGrid[i+1][j+1]);
                temp.push_back(mGrid[i][j+1]);

                temp.push_back(mGrid[i][j]);
                temp.push_back(mGrid[i+1][j]);
                temp.push_back(mGrid[i+1][j+1]);
            }

        }

        return temp;
    }


};

//sende inn x og y i denne oppgaven, men for OpenGL prosjektet måtte man ha sendt inn x og z
bool checkBarycentric(gsl::Vector3D p1, gsl::Vector3D p2, gsl::Vector3D p3, gsl::Vector3D mTarget)
{
    gsl::Vector2D target(mTarget.x, mTarget.y);
    gsl::Vector3D baryC = target.barycentricCoordinates(gsl::Vector2D(p1.x,p1.y),gsl::Vector2D(p2.x,p2.y),gsl::Vector2D(p3.x,p3.y));
    if(baryC.x >=0.f && baryC.y >= 0.f && baryC.z >= 0.f)
        return true;

    return false;
}


int main()
{

    //-----------For Newton ----------------------
    //    NewtonsMovementLaw newton;

    //    newton.calcNormal3Pts(gsl::Vector3D(0,1,0), gsl::Vector3D(2,2,0), gsl::Vector3D(1,0,2));
    //    newton.newtonsSecondLawAcceleration();
    //    gsl::Vector3D acceleration(newton.getAcceleration());


    //    std::cout << "Acceleration: "<< acceleration << std::endl;
    //    std::cout << "Velocity after 1 second: " << newton.calcNewVelocity(1,gsl::Vector3D(0,0,0),acceleration) << std::endl;
    //--------------------------END--------------------------------------

    //------------For Eksamensoppgave 1, H 2018 -----------------------------

    Grid matrise;
    std::vector<gsl::Vector3D> points;
    points.push_back(gsl::Vector3D(0.f,0.75f,2.0f));
    points.push_back(gsl::Vector3D(0.1f,1.8f,1.0f));
    points.push_back(gsl::Vector3D(0.90f,3.42f,2.0f));
    points.push_back(gsl::Vector3D(2.91f,1.23f,0.75f));
    points.push_back(gsl::Vector3D(6.f,2.4f,0.0f));
    points.push_back(gsl::Vector3D(5.25f,0.49f,0.40f));

    points.push_back(gsl::Vector3D(2.21f,2.71f,0.25f));
    points.push_back(gsl::Vector3D(1.88f,0.88f,1.5f));
    points.push_back(gsl::Vector3D(2.14f,4.f,1.0f));
    points.push_back(gsl::Vector3D(4.33f,0.f,1.0f));
    points.push_back(gsl::Vector3D(3.88f,3.80f,0.5f));
    points.push_back(gsl::Vector3D(5.25f,0.78f,0.6f));

    matrise.setMat(points);

    matrise.print(0);
    std::cout << std::endl;


    // [2][1].z og [3][2].z må settes selv for de var ikke satt

//    matrise.mGrid[2][1].z = something;
//    matrise.mGrid[3][2].z = something;



    // Oppgave a.
    // Printe z, Dette bør tegnes opp egentlig.
    matrise.print(1);

    // Oppgave b. Tegn opp en triangulering
    std::cout << "Oppgave 2" << std::endl;
    matrise.print(2);

    std::vector<gsl::Vector3D> triangles = matrise.triangulate();

    for(int i = 0; i< triangles.size() - 2; i+=3)
        std::cout << " T " << triangles.at(i).x << " " <<  triangles.at(i).y  << " | " <<triangles.at(i+1).x << " " <<  triangles.at(i+1).y << " | " <<  triangles.at(i+2).x << " " <<  triangles.at(i+2).y << std::endl;

    //Oppgave c. Forklar hvorfor dette er en god metode å lage en triangulering på for et datasett med høy oppløsning.
    //Dette er en fin måte å forenkel punktdataene på siden de ligger irregulært og med så høy oppløsning at man ikke har bruk for alle punktene.
    //Den generelle algoritmen for å generere en Delaunay triangulering tar veldig lang tid. Denne metoden som kalles en regulær triangulering.


    //Oppgave d. En ball med masse m = 1,
    //ligger i ro i (0,4,2) og slippes.
    //Regn ut ballens akselerasjonsvektor a = [ax,ay,az],
    //for de tre første trekantene ballen ruller på.

    NewtonsMovementLaw newton2;
    gsl::Vector3D ballCoord(0,4,2);
    bool isFound = false;
    int tri1{-1};
    int tri2{-1};
    int tri3{-1};
    gsl::Vector3D oldVelocity{0,0,0};

    //Den første trekanten:
    int triangleNumber1{0};
    for(int i = 0; i < triangles.size() - 2; i+=3)
    {
        if(checkBarycentric(triangles.at(i),triangles.at(i+1), triangles.at(i+2), ballCoord))
        {

            newton2.calcNormal3Pts(triangles.at(i),triangles.at(i+1), triangles.at(i+2));
            isFound = true;
            // std::cout << " T "<< i <<": " <<  triangles.at(i) << " " << triangles.at(i+1) << " " <<  triangles.at(i+2) << std::endl;
            tri1 = triangleNumber1;

            break;

        }
        triangleNumber1++;
    }

    if(isFound)
    {
        newton2.newtonsSecondLawAcceleration();

        std::cout << "Triangle: " <<tri1 << std::endl;
        std::cout <<"Velocity: " << oldVelocity << std::endl;
        std::cout << "Acceleration: " << newton2.getAcceleration() << std::endl;
        std::cout <<"Ball Coord " << ballCoord << std::endl;
        //        std::cout <<" Normal: " << newton2.getNormal() << std::endl;
        std::cout << std::endl;
    }



    isFound = false;
    float deltaTime= 0.0001f;
    int num = 0;

    //Den andre trekanten:
    //Itererer igjennom maks 100 ganger.
    while(num < 100)
    {
        // Legger til bevegelse til ballen.
        oldVelocity = newton2.calcNewVelocity(deltaTime, oldVelocity,newton2.getAcceleration());
        ballCoord = ballCoord + oldVelocity;


        int triangleNumber{0};
        //T2
        for(int i = 0; i < triangles.size() - 2; i+=3)
        {
            if(checkBarycentric(triangles.at(i),triangles.at(i+1), triangles.at(i+2), ballCoord))
            {
                //Må passe på at den ikke stopper ved trekanten som allerede er funnet.
                if(tri1 == triangleNumber)
                {

                }
                else
                {
                    newton2.calcNormal3Pts(triangles.at(i),triangles.at(i+1), triangles.at(i+2));
                    isFound = true;
                    // std::cout << " T "<< i <<": " <<  triangles.at(i) << " " << triangles.at(i+1) << " " <<  triangles.at(i+2) << std::endl;

                    tri2 = triangleNumber;
                    break;
                }
            }
            triangleNumber++;
        }
        if(isFound)
            break;


        num++;
    }
    if(isFound)
    {
        newton2.newtonsSecondLawAcceleration();

        std::cout << "Triangle: " <<tri2 << std::endl;
        std::cout <<"Velocity: " << oldVelocity << std::endl;
        std::cout << "Acceleration: " << newton2.getAcceleration() << std::endl;
        std::cout <<"Ball Coord " << ballCoord << std::endl;
        // std::cout <<" Normal: " << newton2.getNormal() << std::endl;
        std::cout << std::endl;

    }
    // add movement to the ball

    isFound = false;
    num = 0;

    //Den tredje trekanten:

    while(num < 100)
    {
        // Legger til bevegelse til ballen.
        oldVelocity = newton2.calcNewVelocity(deltaTime, oldVelocity,newton2.getAcceleration());
        ballCoord = ballCoord + oldVelocity;

        int triangleNumber{0};
        for(int i = 0; i < triangles.size() - 2; i+=3)
        {
            if(checkBarycentric(triangles.at(i),triangles.at(i+1), triangles.at(i+2), ballCoord))
            {
                //Må passe på at den ikke stopper ved trekantene som allerede er funnet.
                if(tri2 == triangleNumber || tri1 == triangleNumber)
                {

                }
                else
                {
                    newton2.calcNormal3Pts(triangles.at(i),triangles.at(i+1), triangles.at(i+2));
                    isFound = true;
                    //                    std::cout << " T "<< i <<": " <<  triangles.at(i) << " " << triangles.at(i+1) << " " <<  triangles.at(i+2) << std::endl;

                    tri3 = triangleNumber;
                    break;
                }
            }
            triangleNumber++;
        }

        if(isFound)
            break;
        num++;
    }
    if(isFound)
    {
        newton2.newtonsSecondLawAcceleration();

        std::cout << "Triangle: " <<tri3 << std::endl;
        std::cout <<"Velocity: " << oldVelocity << std::endl;
        std::cout << "Acceleration: " << newton2.getAcceleration() << std::endl;
        std::cout <<"Ball Coord " << ballCoord << std::endl;

        std::cout << std::endl;
    }


    //Triangel 6,9,12 er de tre første.
    //a1 akselerasjon: 6: 4.0,  -4.0,  -1.8    //Coord:    0  , 4   , 2
    //a2 akselerasjon: 8: 2.31, -2.31, -0.56  //Coord: ca: 1.0, 2.98, 1.54
    //a3 akselerasjon: 0: 2.14, 4.28, -1.25  //Coord: ca: 2.0, 1.98, 1.12 //Denne trengs ikke i oppgave f)

    //Oppgave e)
    //Hva er ballens koordinater når den begynner å endre retning?
    //Koordinatene er 2,2 når den begynnter å snu retning.

    //Oppgave f)
    //Vi antar at ballen hele tiden ruller på en trekant,og at de tre første trekantene er Ti, Tj, Tk.
    //Regn ut tiden det tar til ballen ruller over fra Ti til Tj og fra Tj til Tk.

    //p = deltaposisjon, lengden mellom posisjonene.
    //p = v0*t +1/2* a*t^2

    //Første triangel. v0 = 0; Som gjør at v0*t er 0.
    //p = lengden mellom (0,4,2) og (1,4,1.5)
   gsl::Vector3D pt1 (0.f,4.f,2.f);
   gsl::Vector3D pt2 (1.f,4.f,1.5f);
   gsl::Vector3D pt3 (2.f,2.f,0.5f);
  // gsl::Vector3D Tj2 (2)

   float p1 = pt2.lengthBetVec3d(pt1);
   float p2 = pt3.lengthBetVec3d(pt2);

   //t1 = kvadratrot(2*p1/a1)
   gsl::Vector3D t = gsl::Vector3D(sqrt(2*p1/4),sqrt(2*p1/-4), sqrt(2*p1/-1.8));
   std::cout << "Tid = " << t << std::endl;

   //t2 = kvadratrot(2*p2/a2)
   gsl::Vector3D t2 = gsl::Vector3D(sqrt(2*p2/2.31),sqrt(2*p2/-2.31), sqrt(2*p2/-0.56));
   std::cout << "Tid = " << t2 << std::endl;


    //--------------------------END--------------------------------------


    return 0;
}
