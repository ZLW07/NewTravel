//
// Created by wei on 2023/5/8.
//

#include "ut_pqp.h"
#include "Log/log.h"
#include "PQP/PQP.h"
#include <math.h>
#include <stdio.h>

#define PI    3.14159265359
#define LISTS 0
#include "PQP/MatVec.h"
TEST_F(UTPQP, Colli)
{
    // initialize PQP model pointers

    PQP_Model *b1 = new PQP_Model;
    PQP_Model *b2 = new PQP_Model;

    // Add trianges to form tori

    ZLOG_INFO << "loading tris into PQP_Model objects...";

    PQP_REAL a = (PQP_REAL)1.0; // major radius of the tori
    PQP_REAL b = (PQP_REAL)0.2; // minor radius of the tori

    int n1 = 50; // tori will have n1*n2*2 triangles each
    int n2 = 50;

    int uc, vc;
    int count = 0;

    b1->BeginModel();
    b2->BeginModel();
    for (uc = 0; uc < n1; uc++)
    {
        for (vc = 0; vc < n2; vc++)
        {
            PQP_REAL u1 = (PQP_REAL)(2.0 * PI * uc) / n1;
            PQP_REAL u2 = (PQP_REAL)(2.0 * PI * (uc + 1)) / n1;
            PQP_REAL v1 = (PQP_REAL)(2.0 * PI * vc) / n2;
            PQP_REAL v2 = (PQP_REAL)(2.0 * PI * (vc + 1)) / n2;

            PQP_REAL p1[3], p2[3], p3[3], p4[3];

            p1[0] = (a - b * cos(v1)) * cos(u1);
            p2[0] = (a - b * cos(v1)) * cos(u2);
            p3[0] = (a - b * cos(v2)) * cos(u1);
            p4[0] = (a - b * cos(v2)) * cos(u2);
            p1[1] = (a - b * cos(v1)) * sin(u1);
            p2[1] = (a - b * cos(v1)) * sin(u2);
            p3[1] = (a - b * cos(v2)) * sin(u1);
            p4[1] = (a - b * cos(v2)) * sin(u2);
            p1[2] = b * sin(v1);
            p2[2] = b * sin(v1);
            p3[2] = b * sin(v2);
            p4[2] = b * sin(v2);

            b1->AddTri(p1, p2, p3, count);
            b1->AddTri(p4, p2, p3, count + 1);
            b2->AddTri(p1, p2, p3, count);
            b2->AddTri(p4, p2, p3, count + 1);

            count += 2;
        }
    }

    ZLOG_INFO << "done";
    ZLOG_INFO << "Tori have  triangles each" << count;
    ZLOG_INFO << "building hierarchies...";
    b1->EndModel();
    b2->EndModel();
    b1->MemUsage(1);
    b2->MemUsage(1);

    // now we are free to call the proximity routines.
    // but first, construct the transformations that define the placement
    // of our two hierarchies in world space:

    // this placement causes them to overlap a large amount.

    PQP_REAL R1[3][3], R2[3][3], T1[3], T2[3];

    R1[0][0] = R1[1][1] = R1[2][2] = 1.0;
    R1[0][1] = R1[1][0] = R1[2][0] = 0.0;
    R1[0][2] = R1[1][2] = R1[2][1] = 0.0;

    R2[0][0] = R2[1][1] = R2[2][2] = 1.0;
    R2[0][1] = R2[1][0] = R2[2][0] = 0.0;
    R2[0][2] = R2[1][2] = R2[2][1] = 0.0;

    T1[0] = 1.0;
    T1[1] = 0.0;
    T1[2] = 0.0;
    T2[0] = 0.0;
    T2[1] = 0.0;
    T2[2] = 0.0;

    // perform a collision query

    PQP_CollideResult cres;
    PQP_Collide(&cres, R1, T1, b1, R2, T2, b2, PQP_ALL_CONTACTS);

    // looking at the report, we can see where all the contacts were, and
    // also how many tests were necessary:

    ZLOG_INFO << "All contact collision query between overlapping tori:";
    ZLOG_INFO << "Num BV tests: " << cres.NumBVTests();
    ZLOG_INFO << "Num Tri tests: " << cres.NumTriTests();
    ZLOG_INFO << "Num contact pairs: " << cres.NumPairs();
#if 0
    int i;
    for (i = 0; i < cres.NumPairs(); i++)
    {
        ZLOG_INFO << "contact: " << i << ", tri: " << cres.Id1(i) << ", tri: " <<  cres.Id2(i);
    }
#endif

    // Notice the PQP_ALL_CONTACTS flag we used in the call to PQP_Collide.
    // The alternative is to use the PQP_FIRST_CONTACT flag, instead.
    // The result is that the collide routine searches for any contact,
    // but not all of them.  It can take many many fewer tests to locate a single
    // contact.

    PQP_Collide(&cres, R1, T1, b1, R2, T2, b2, PQP_FIRST_CONTACT);

    ZLOG_INFO << "First contact collision query between overlapping tori:";
    ZLOG_INFO << "Num BV tests: " << cres.NumBVTests();
    ZLOG_INFO << "Num Tri tests: " << cres.NumTriTests();
    ZLOG_INFO << "Num contact pairs: " << cres.NumPairs();
#if 1
    for (int i = 0; i < cres.NumPairs(); i++)
    {
        ZLOG_INFO << "contact: " << i << ", tri: " << cres.Id1(i) << ", tri: " << cres.Id2(i);
    }
#endif

    // Perform a distance query, which should return a distance of 0.0

    PQP_DistanceResult dres;
    PQP_Distance(&dres, R1, T1, b1, R2, T2, b2, 0.0, 0.0);
    ZLOG_INFO << "Distance query between overlapping tori:";
    ZLOG_INFO << "Num BV tests: " << cres.NumBVTests();
    ZLOG_INFO << "Num Tri tests: " << cres.NumTriTests();
    ZLOG_INFO << "Distance " << dres.Distance();

    // by rotating one of them around the x-axis 90 degrees, they
    // are now interlocked, but not quite touching.

    R1[0][0] = 1.0;
    R1[0][1] = 0.0;
    R1[0][2] = 0.0;
    R1[1][0] = 0.0;
    R1[1][1] = 0.0;
    R1[1][2] = -1.0;
    R1[2][0] = 0.0;
    R1[2][1] = 1.0;
    R1[2][2] = 0.0;

    PQP_Collide(&cres, R1, T1, b1, R2, T2, b2, PQP_FIRST_CONTACT);

    ZLOG_INFO << "Collision query between interlocked but nontouching tori:";
    ZLOG_INFO << "Num BV tests: " << cres.NumBVTests();
    ZLOG_INFO << "Num Tri tests: " << cres.NumTriTests();
    ZLOG_INFO << "Num contact pairs: " << cres.NumPairs();
#if 1
    for (int i = 0; i < cres.NumPairs(); i++)
    {
        ZLOG_INFO << "contact: " << i << ", tri: " << cres.Id1(i) << ", tri: " << cres.Id2(i);
    }
#endif

    // Perform a distance query - the distance found should be greater than zero

    PQP_Distance(&dres, R1, T1, b1, R2, T2, b2, 0.0, 0.0);
    ZLOG_INFO << "Distance query between interlocked but nontouching tori:";
    ZLOG_INFO << "Num BV tests: " << cres.NumBVTests();
    ZLOG_INFO << "Num Tri tests: " << cres.NumTriTests();
    ZLOG_INFO << "Distance " << dres.Distance();

    // Perform two tolerance queries. One tolerance setting is greater than the
    // distance between the models, and one tolerance is less than the distance.

    PQP_ToleranceResult tres;
    PQP_REAL tolerance = (PQP_REAL)0.60;
    PQP_Tolerance(&tres, R1, T1, b1, R2, T2, b2, tolerance);

    ZLOG_INFO << "Tolerance query between interlocked but nontouching tori: " << tolerance << "with tolerance";
    ZLOG_INFO << "Num BV tests: " << cres.NumBVTests();
    ZLOG_INFO << "Num Tri tests: " << cres.NumTriTests();
    ZLOG_INFO << "Closer than tolerance? " << tolerance;
    if (tres.CloserThanTolerance())
    {
        ZLOG_INFO << "yes.";
    }
    else
    {
        ZLOG_INFO << "no.";
    }

    //
    //    printf("\nTolerance query between interlocked but nontouching tori\n"
    //           "with tolerance %lf\n",
    //        tolerance);
    //    printf("Num BV tests: %d\n", tres.NumBVTests());
    //    printf("Num Tri tests: %d\n", tres.NumTriTests());
    //    printf("Closer than tolerance? ", tolerance);
    //    if (tres.CloserThanTolerance())
    //        printf("yes.\n");
    //    else
    //        printf("no.\n");
    //
    //    tolerance = (PQP_REAL).40;
    //    PQP_Tolerance(&tres, R1, T1, b1, R2, T2, b2, tolerance);
    //
    //    printf("\nTolerance query between interlocked but nontouching tori\n"
    //           "with tolerance %lf\n",
    //        tolerance);
    //    printf("Num BV tests: %d\n", tres.NumBVTests());
    //    printf("Num Tri tests: %d\n", tres.NumTriTests());
    //    printf("Closer than tolerance? ", tolerance);
    //    if (tres.CloserThanTolerance())
    //        printf("yes.\n");
    //    else
    //        printf("no.\n");
    //
    //    // by moving one of the tori closer to the other, they
    //    // almost touch.  This is the case that requires a lot
    //    // of work wiht methods which use bounding boxes of limited
    //    // aspect ratio.  Oriented bounding boxes are more efficient
    //    // at determining noncontact than spheres, octree, or axis-aligned
    //    // bounding boxes for scenarios like this.  In this case, the interlocked
    //    // tori are separated by 0.0001 at their closest point.
    //
    //    T1[0] = (PQP_REAL)1.5999;
    //
    //    PQP_Collide(&cres, R1, T1, b1, R2, T2, b2, PQP_FIRST_CONTACT);
    //
    //    printf("\nCollision query on interlocked and almost touching tori:\n");
    //    printf("Num BV tests: %d\n", cres.NumBVTests());
    //    printf("Num Tri tests: %d\n", cres.NumTriTests());
    //    printf("Num contact pairs: %d\n", cres.NumPairs());
    //#if LISTS
    //    for (i = 0; i < cres.NumPairs(); i++)
    //    {
    //        printf("\t contact %4d: tri %4d and tri %4d\n", i, cres.Id1(i), cres.Id2(i));
    //    }
    //#endif
    //
    //    PQP_Distance(&dres, R1, T1, b1, R2, T2, b2, 0.0, 0.0);
    //
    //    printf("\nDistance query between interlocked and almost touching tori\n");
    //    printf("Num BV tests: %d\n", dres.NumBVTests());
    //    printf("Num Tri tests: %d\n", dres.NumTriTests());
    //    printf("Distance: %lf\n", dres.Distance());
    //
    //    tolerance = (PQP_REAL)0.00015;
    //    PQP_Tolerance(&tres, R1, T1, b1, R2, T2, b2, tolerance);
    //
    //    printf("\nTolerance query between interlocked and almost touching tori\n"
    //           "with tolerance %lf\n",
    //        tolerance);
    //    printf("Num BV tests: %d\n", tres.NumBVTests());
    //    printf("Num Tri tests: %d\n", tres.NumTriTests());
    //    printf("Closer than tolerance? ", tolerance);
    //    if (tres.CloserThanTolerance())
    //        printf("yes.\n");
    //    else
    //        printf("no.\n");
    //
    //    tolerance = (PQP_REAL)0.00005;
    //    PQP_Tolerance(&tres, R1, T1, b1, R2, T2, b2, tolerance);
    //
    //    printf("\nTolerance query between interlocked and almost touching tori\n"
    //           "with tolerance %lf\n",
    //        tolerance);
    //    printf("Num BV tests: %d\n", tres.NumBVTests());
    //    printf("Num Tri tests: %d\n", tres.NumTriTests());
    //    printf("Closer than tolerance? ", tolerance);
    //    if (tres.CloserThanTolerance())
    //        printf("yes.\n");
    //    else
    //        printf("no.\n");

    delete b1;
    delete b2;
}

TEST_F(UTPQP, Get_covariance_triverts)
{
    Tri *pTri = new Tri();
    double p1[3], p2[3], p3[3];
    p1[0] = 1.5;
    p1[1] = 0.8;
    p1[2] = 2.5;

    p2[0] = 3.4;
    p2[1] = 2.1;
    p2[2] = 5.2;

    p3[0] = 3.5;
    p3[1] = 7.8;
    p3[2] = 2.6;
    memcpy(pTri->p1, p1, sizeof(double) * 3);
    memcpy(pTri->p2, p2, sizeof(double) * 3);
    memcpy(pTri->p3, p3, sizeof(double) * 3);
    pTri->id = 0;
    PQP_REAL M[3][3];
    get_covariance_triverts(M, pTri, 1);
    for(int ii = 0; ii < 3; ii++)
    {
        ZLOG_INFO << M[ii][0] << ", " << M[ii][1] <<", " << M[ii][2];
    }
    PQP_REAL C[3][3], E[3][3], R[3][3], s[3], axis[3], mean[3], coord;
    Meigen(E, s, M);
    for(int ii = 0; ii < 3; ii++)
    {
        ZLOG_INFO << E[ii][0] << ", " << E[ii][1] <<", " << E[ii][2];
    }
    ZLOG_INFO << s[0] << ", " << s[1] <<", " <<s[2];

    int min, mid, max;
    if (s[0] > s[1])
    {
        max = 0;
        min = 1;
    }
    else
    {
        min = 0;
        max = 1;
    }
    if (s[2] < s[min])
    {
        mid = min;
        min = 2;
    }
    else if (s[2] > s[max])
    {
        mid = max;
        max = 2;
    }
    else
    {
        mid = 2;
    }
    McolcMcol(R, 0, E, max);
    McolcMcol(R, 1, E, mid);
    R[0][2] = E[1][max] * E[2][mid] - E[1][mid] * E[2][max];
    R[1][2] = E[0][mid] * E[2][max] - E[0][max] * E[2][mid];
    R[2][2] = E[0][max] * E[1][mid] - E[0][mid] * E[1][max];
    for(int ii = 0; ii < 3; ii++)
    {
        ZLOG_INFO << R[ii][0] << ", " << R[ii][1] <<", " << R[ii][2];
    }
}