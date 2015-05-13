#include "Scene.h"
#include <time.h>
#include <math.h>
#include <GL/gl.h>
#include "opengl.h"

void draw_axes(){
    glLineWidth(5);
    glBegin(GL_LINES);

    glColor3f( 1.f, 0.f, 0.f);
    glVertex3f( 0.f, 0.f, 0.f);
    glVertex3f( 1.f, 0.f, 0.f);

    glColor3f( 0.f, 1.f, 0.f);
    glVertex3f( 0.f, 0.f, 0.f);
    glVertex3f( 0.f, 1.f, 0.f);

    glColor3f( 0.f, 0.f, 1.f);
    glVertex3f( 0.f, 0.f, 0.f);
    glVertex3f( 0.f, 0.f, 1.f);

    glEnd();
}

void draw_grid(){
    int i;
    glLineWidth(1);
    glColor3f( 1.f, 1.f, 1.f);

    glPushMatrix();
    glTranslatef( -5, 0, -5);

    glBegin( GL_LINES );

    for (i=0;i<=10;++i)
    {
        glVertex3f( i, 0, 0);
        glVertex3f( i, 0, 10);
    }

    for (i=0;i<=10;++i)
    {
        glVertex3f( 0, 0, i);
        glVertex3f( 10, 0, i);
    }

    glEnd();
    glPopMatrix();
}

void draw_cube(){
    static float pt[8][3] = { {0,0,0}, {1,0,0}, {1,0,1}, {0,0,1}, {0,1,0}, {1,1,0}, {1,1,1}, {0,1,1} };
    static int f[6][4] = { {0,1,2,3}, {5,4,7,6}, {1,5,6,2}, {0,3,7,4}, {3,2,6,7}, {0,4,5,1} };
    static float n[6][3] = { {0,-1,0}, {0,1,0}, {1,0,0}, {-1,0,0}, {0,0,1}, {0,0,-1} };
    static float uv[6][4][2] = { { {0,0}, {1,0}, {1,1}, {0,1} },
                                 { {0,0}, {1,0}, {1,1}, {0,1} },
                                 { {0,0}, {1,0}, {1,1}, {0,1} },
                                 { {0,0}, {1,0}, {1,1}, {0,1} },
                                 { {0,0}, {1,0}, {1,1}, {0,1} },
                                 { {0,0}, {1,0}, {1,1}, {0,1} } };
    int i,j;

    glTranslatef(-0.5,-0.5,-0.5);
    glBegin(GL_QUADS);
    for (i=0;i<6;i++)
    {
        glNormal3f( n[ i ][0], n[ i ][1], n[ i ][2] );
        for (j=0;j<4;j++)
        {
            glTexCoord2f( uv[i][j][0], uv[i][j][1] );
            glVertex3f( pt[ f[i][j] ][0], pt[ f[i][j] ][1], pt[ f[i][j] ][2] );
        }
    }
    glEnd();
}

void draw_cube_map(){
    static float pt[8][3] = { {0,0,0}, {1,0,0}, {1,0,1}, {0,0,1}, {0,1,0}, {1,1,0}, {1,1,1}, {0,1,1} };
    static int f[6][4] = { {0,1,2,3}, {5,4,7,6}, {1,5,6,2}, {0,3,7,4}, {3,2,6,7}, {0,4,5,1} };
    static float n[6][3] = { {0,-1,0}, {0,1,0}, {1,0,0}, {-1,0,0}, {0,0,1}, {0,0,-1} };
    static float uv[6][4][2] = { { {1.0/2,1.0/3}, {1.0/4,1.0/3}, {1.0/4,0}, {1.0/2,0} }, /* face du bas */
                                 { {1.0/4,2.0/3}, {1.0/2,2.0/3}, {1.0/2,1}, {1.0/4,1} }, /* face du haut */
                                 { {1.0/4,1.0/3}, {1.0/4,2.0/3}, {0,2.0/3}, {0/4,1.0/3} }, /* face DR */
                                 { {1.0/2,1.0/3}, {3.0/4,1.0/3}, {3.0/4,2.0/3}, {1.0/2,2.0/3} }, /* face GA */
                                 { {3.0/4,1.0/3}, {1,1.0/3}, {1,2.0/3}, {3.0/4,2.0/3} }, /* face arriere */
                                 { {1.0/2,1.0/3}, {1.0/2,2.0/3}, {1.0/4,2.0/3}, {1.0/4,1.0/3} } }; /* face avant */
    int i,j;

    glTranslatef(-0.5,-0.5,-0.5);
    glBegin(GL_QUADS);
    for (i=0;i<6;i++)
    {
        glNormal3f(- n[ i ][0], - n[ i ][1], - n[ i ][2] );
        for (j=0;j<4;j++)
        {
            glTexCoord2f( uv[i][j][0], uv[i][j][1] );
            glVertex3f( pt[ f[i][j] ][0], pt[ f[i][j] ][1], pt[ f[i][j] ][2] );
        }
    }
    glEnd();
}

void draw_sphere(){
    int i,j;
    float a,a2,b;
    int N = 20;
    for(i = 0;i < N; i++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        a = M_PI * i / N;
        a2 = M_PI * (i + 1) / N;
        for(j = 0;j <= N; j++)
        {
            b = 2.0 * M_PI * j / N;
            glNormal3f(sin(a)*cos(b),cos(a),sin(a)*sin(b));
            glVertex3f(sin(a)*cos(b),cos(a),sin(a)*sin(b));
            glNormal3f(sin(a2)*cos(b),cos(a2),sin(a2)*sin(b));
            glVertex3f(sin(a2)*cos(b),cos(a2),sin(a2)*sin(b));
        }
        glEnd();
    }

}

void draw_cylinder(){
    int i;

    glBegin(GL_TRIANGLE_STRIP);
    int N = 20;
    float a;
    for(i = 0; i <= N; i++)
    {
        a = 2.0 * i * M_PI / N;
        glNormal3f(cos(a), 0, sin(a));
        glVertex3f(cos(a), 0, sin(a));
        glNormal3f(cos(a), 0, sin(a));
        glVertex3f(cos(a), 1, sin(a));
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 1, 0);
    glVertex3f(0, 1, 0);
    for(i = 0; i <= N; i++)
    {
        a = 2.0 * i * M_PI / N;
        glNormal3f(0, 1, 0);
        glVertex3f(cos(a), 1, sin(a));
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, -1, 0);
    glVertex3f(0, 0, 0);
    for(i = 0; i <= N; i++)
    {
        a = 2.0 * i * M_PI / N;
        glNormal3f(0, -1, 0);
        glVertex3f(cos(a), 0, sin(a));
    }
    glEnd();

}

void draw_cone(){
    int i;

    glBegin(GL_TRIANGLES);
    int N=20;
    float a;
    for(i=0;i<=N;i++)
    {
        a=2.0*i*M_PI/N;
        glNormal3f(0,0,0);
        glVertex3f(0,0,0);
        glNormal3f(cos(a),0,sin(a));
        glVertex3f(cos(a),1,sin(a));
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0,1,0);
    glVertex3f(0,1,0);
    for(i=0;i<=N;i++)
    {
        a=2.0*i*M_PI/N;
        glNormal3f(0,1,0);
        glVertex3f(cos(a),1,sin(a));
    }
    glEnd();

}

void Normal(const Image& im, int i, int j){
    Vec3f G, D, H, B, GD, BH, N;
    vecInit(G, i - 1, getPix(im, i - 1, j, 0), j);
    vecInit(D, i + 1, getPix(im, i + 1, j, 0), j);
    vecInit(B,i,getPix(im, i, j - 1, 0), j + 1);
    vecInit(H,i,getPix(im, i, j + 1, 0),j - 1);
    vecSub(GD, D, G);
    vecSub(BH, H, B);
    vecCross(N, GD, BH);
    glNormal3f(N.x, N.y, N.z);
}

void draw_arbre (){
    glPushMatrix();
    glBegin( GL_QUADS );
    glNormal3f( 0,1,0);
    glTexCoord2f( 1,1);
    glVertex3f( 0.5, 1, 0);
    glTexCoord2f( 0, 1);
    glVertex3f( -0.5, 1, 0);
    glTexCoord2f( 0,0);
    glVertex3f( -0.5, 0, 0);
    glTexCoord2f( 1,0);
    glVertex3f( 0.5, 0, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glTexCoord2f(1,1);
    glVertex3f(0,1,-0.5);
    glTexCoord2f(0,1);
    glVertex3f(0,1,0.5);
    glTexCoord2f(0,0);
    glVertex3f(0,0,0.5);
    glTexCoord2f(1,0);
    glVertex3f(0,0,-0.5);
    glEnd();
    glPopMatrix();
}

void DessineTerrain(const Image &ter){
    int i, j;
    glPushMatrix();
    glScalef(1,0.1,1);
    glTranslatef(-100,-200,-100);
    for(i = 1;i<imGetDimX(ter) - 2;i++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for(j = 1;j < imGetDimY(ter) - 1; j++)
        {
            glTexCoord2f(((float)i) /imGetDimX(ter), ((float)j) /imGetDimY(ter));
            Normal(ter,i,j);
            glVertex3f(i,getPix(ter,i,j,0),j);
            glTexCoord2f(((float)(i + 1)) /imGetDimX(ter), ((float)j) /imGetDimY(ter));
            Normal(ter,i+1,j);
            glVertex3f(i+1,getPix(ter,i+1,j,0),j);

        }
        glEnd();
    }
    glPopMatrix();
}

void dessin_foret(const Image &ter){
    int i, j;
    int percent;
    for(i = 0; i < imGetDimX(ter) - 1; i++){
        for(j = 0; j < imGetDimY(ter) -1; j++){
            if((float(getPix(ter, i, j, 0)))/20 > 2 && (float(getPix(ter, i, j, 0)))/20 < 6)
            {
                percent = rand()%1000;
                if(percent < 3){
                    glPushMatrix();
                    glTranslatef((float(i))/2, (float(getPix(ter, i, j, 0)))/20, (float(j))/2);
                    glScalef(4,4,4);
                    draw_arbre();
                    glPopMatrix();
                }
            }
        }
    }
}

void draw_voiture(){
    glPushMatrix(); // roue
    glTranslatef(2,1,-2);
    glRotatef(90,1,0,0);
    glScalef(1,1,1);
    glColor3f(0.2,0.2,0.2);
    draw_cylinder();
    glPopMatrix();

    glPushMatrix(); // roue
    glTranslatef(2,1,1);
    glRotatef(90,1,0,0);
    glScalef(1,1,1);
    glColor3f(0.2,0.2,0.2);
    draw_cylinder();
    glPopMatrix();

    glPushMatrix(); // roue
    glTranslatef(-2,1,1);
    glRotatef(90,1,0,0);
    glScalef(1,1,1);
    glColor3f(0.2,0.2,0.2);
    draw_cylinder();
    glPopMatrix();

    glPushMatrix(); // roue
    glTranslatef(-2,1,-2);
    glRotatef(90,1,0,0);
    glScalef(1,1,1);
    glColor3f(0.2,0.2,0.2);
    draw_cylinder();
    glPopMatrix();

    glPushMatrix(); // avant arriere
    glTranslatef(0,1.5,0);
    glScalef(6,1,2);
    glColor3f(1,1,0);
    draw_cube();
    glPopMatrix();

    glPushMatrix(); // base
    glTranslatef(0,2,0);
    glScalef(3,2,2);
    glColor3f(1,1,0);
    draw_cube();
    glPopMatrix();

    glPushMatrix(); // base
    glTranslatef(-2,2,0);
    glRotatef(90,0,1,0);
    glScalef(0.1,2,2);
    glColor3f(1,1,1);
    draw_cube();
    glPopMatrix();

    glPushMatrix(); // base
    glTranslatef(-2,2,-0.9);
    glRotatef(90,0,1,0);
    glScalef(0.1,2,2);
    glColor3f(1,1,1);
    draw_cube();
    glPopMatrix();

    glPushMatrix(); // base
    glTranslatef(-2,2,0.9);
    glRotatef(90,0,1,0);
    glScalef(0.1,2,2);
    glColor3f(1,1,1);
    draw_cube();
    glPopMatrix();

    glPushMatrix(); // base
    glTranslatef(2,2,0);
    glRotatef(52,0,0,1);
    glScalef(1,2,2);
    glColor3f(1,1,1);
    draw_cube();
    glPopMatrix();
}

void draw_fly(){
    glPushMatrix(); //tronc
    glTranslatef(0,0.5,0);
    glScalef(1,5,1);
    draw_sphere();
    glPopMatrix();

    glPushMatrix(); //aile avant droite
    glTranslatef(2.4,1,0);
    glScalef(7,2,0.25);
    draw_cube();
    glPopMatrix();

    glPushMatrix(); //réacteur droit
    glTranslatef(2,1,0.375);
    glScalef(0.25,1.5,0.3);
    draw_sphere();
    glPopMatrix();

    glPushMatrix(); //réacteur droit
    glTranslatef(4,1,0.375);
    glScalef(0.25,1.5,0.3);
    draw_sphere();
    glPopMatrix();

    glPushMatrix(); //aile avant gauche
    glTranslatef(-2.4,1,0);
    glScalef(7,2,0.25);
    draw_cube();
    glPopMatrix();

    glPushMatrix(); //réacteur gauche1
    glTranslatef(-2,1,0.375);
    glScalef(0.25,1.5,0.3);
    draw_sphere();
    glPopMatrix();

    glPushMatrix(); //réacteur gauche2
    glTranslatef(-4,1,0.375);
    glScalef(0.25,1.5,0.3);
    draw_sphere();
    glPopMatrix();

    glPushMatrix(); //aileron
    glTranslatef(0,-3.5,-0.9);
    glScalef(0.2,0.8,0.7);
    glRotatef(-15,1,0,0);
    draw_cube();
    glPopMatrix();

    glPushMatrix(); //aile arrière droite
    glTranslatef(1.1,-3,0);
    glScalef(1.4,0.5,0.25);
    glRotatef(0,1,0,0);
    draw_cube();
    glPopMatrix();

    glPushMatrix(); //aile arrière gauche
    glTranslatef(-1.1,-3,0);
    glScalef(1.4,0.5,0.25);
    glRotatef(0,1,0,0);
    draw_cube();
    glPopMatrix();
}

Vec3f calcul_pos(const Animation & ani, float t){
    Vec3f P;
    int te = t;
    float r = t - te;
    int tes = te + 1;

    te = te % ani.nbp;
    tes = tes % ani.nbp;

    P.x = r * ani.P[tes].x + (1 - r) * ani.P[te].x;
    P.y = r * ani.P[tes].y + (1 - r) * ani.P[te].y;
    P.z = r * ani.P[tes].z + (1 - r) * ani.P[te].z;
    return P;
}

void draw_animfly (const Animation & ani){
    Vec3f P, X, Z;
    Vec3f PF, DIR;
    float t;
    float aX;
    float aZ;

    t = temps();
    P = calcul_pos(ani, t);
    PF = calcul_pos(ani, t + 1);
    vecInit(X, 1, 0, 0); /* crée le vecteur X = (1,0,0) */
    vecInit(Z, 0, 0, 1); /* crée le vecteur Y = (0,1,0) */
    vecSub(DIR, PF, P); /* crée le vecteur DIR = PF - p */
    vecNormalize(DIR); /* Normalise le vecteur DIR */
    aX = acos(vecDot(X, DIR)); /* calcule l'angle entre le vecteur X et DIR */
    aX = 180 * aX / M_PI;
    aZ = acos(vecDot(Z, DIR)); /* calcule l'angle entre le vecteur Y et DIR */
    aZ = 10 * aZ / M_PI;

    if (DIR.z > 0){
        aX = -aX;
    }

    if (DIR.y < 0){
        aZ = -aZ;
    }

    glPushMatrix();
    glTranslatef(P.x, P.y, P.z);
    glRotatef(aX,0,1,0);
    glRotatef(aZ,0,0,1);
    glRotatef(90, 1, 0, 0);
    glRotatef(-90, 0, 0, 1);
    draw_fly();
    glPopMatrix();
}

float alti(int i, int j, float t, int gx, int gz){
    float d, z; // d distance entre le point qu'on est en train d'afficher et la goutte

    d = sqrt((gx - i) * (gx - i) + (gz - j) * (gz - j));
    z = (cos(i * d * 20 + t) * 1) / 10; //z : distance entre train de vague et 5 : hauteur de +5. On peut rajouter coeff * devant d pour accélerer la vitesse

    return z;
}

void Dessine_eau(int DX, int DY) //copier normal du terrain et remplacer avec alti
{
    float t = temps();
    int i,j;
    for(i = 0;i <= DX * 2; i++)
    {
        glBegin(GL_QUAD_STRIP);
        for(j = 0;j <= DY * 2; j++)
        {
            glNormal3f(0, ((float)(alti(i, j, t, DX, DY))/2), 0);
            glVertex3f(i,alti(i, j, t, DX, DY),j);
            glNormal3f(0, ((float)(alti(i + 1, j, t, DX, DY))/2), 0);
            glVertex3f(i + 1, alti(i + 1, j, t, DX, DY), j);
        }
        glEnd();
    }
}

void Dessine_Oiseaux(){
    float t = temps();

    glPushMatrix();
    glRotatef(15 * cos(10 * t), 0, 0, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0.5, 1); //A
    glVertex3f(0, 0, 1.2); //A
    glTexCoord2f(0.5, 0); //B
    glVertex3f(0, 0, 0); //B
    glTexCoord2f(0.75, 0); //C
    glVertex3f(1, 0, 0); //C
    glTexCoord2f(0.75, 1); //D
    glVertex3f(1, 0, 1.2); //D
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.96, cos(t*10)/3.85, 0);
    glRotatef(35 * cos(10 * t), 0, 0, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0.75, 1); //C
    glVertex3f(0, 0, 1.2); //C
    glTexCoord2f(0.75, 0); //D
    glVertex3f(0, 0, 0); //D
    glTexCoord2f(1, 0); //E
    glVertex3f(1, 0, 0); //E
    glTexCoord2f(1, 1); //F
    glVertex3f(1, 0, 1.2); //F
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glRotatef(-15 * cos(10 * t),0,0,1);
    glBegin(GL_QUADS);
    glTexCoord2f(0.5, 0); //G
    glVertex3f(0, 0, 0); //A
    glTexCoord2f(0.5, 1); //H
    glVertex3f(0, 0, 1.2); //B
    glTexCoord2f(0.25, 1); //B
    glVertex3f(-1, 0, 1.2); //G
    glTexCoord2f(0.25, 0); //A
    glVertex3f(-1, 0, 0); //H
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.96, cos(t*10)/3.85, 0);
    glRotatef(-35 * cos(10 * t), 0, 0, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0.25, 0); //G
    glVertex3f(0, 0, 0); //G
    glTexCoord2f(0.25, 1); //I
    glVertex3f(0, 0, 1.2); //H
    glTexCoord2f(0, 1); //H
    glVertex3f(-1, 0, 1.2); //I
    glTexCoord2f(0, 0); //J
    glVertex3f(-1, 0, 0); //J
    glEnd();
    glPopMatrix();

}

void draw_animBird (const Animation & ani){
    Vec3f P, X, Z;
    Vec3f PF, DIR;
    float t;
    float aX;
    float aZ;

    t = temps();
    P = calcul_pos(ani, t);
    PF = calcul_pos(ani, t + 1);
    vecInit(X, 1, 0, 0); /* crée le vecteur X = (1,0,0) */
    vecInit(Z, 0, 0, 1); /* crée le vecteur Y = (0,1,0) */
    vecSub(DIR, PF, P); /* crée le vecteur DIR = PF - p */
    vecNormalize(DIR); /* Normalise le vecteur DIR */
    aX = acos(vecDot(X, DIR)); /* calcule l'angle entre le vecteur X et DIR */
    aX = 180 * aX / M_PI;
    aZ = acos(vecDot(Z, DIR)); /* calcule l'angle entre le vecteur Y et DIR */
    aZ = 45 * aZ / M_PI;

    if (DIR.z > 0){
        aX = -aX;
    }

    if (DIR.x > 0){
        aZ = -aZ;
    }

    glPushMatrix();
    glTranslatef(P.x, P.y, P.z);
    glRotatef(90, 0, 1, 0);
    glRotatef(aX,0,1,0);
    glRotatef(aZ,0,0,1);
    Dessine_Oiseaux();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(P.x + 60, P.y + 10, P.z - 40);
    glRotatef(90, 0, 1, 0);
    glRotatef(aX,0,1,0);
    glRotatef(aZ,0,0,1);
    Dessine_Oiseaux();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(P.x + 20, P.y + 20, P.z + 40);
    glRotatef(90, 0, 1, 0);
    glRotatef(aX,0,1,0);
    glRotatef(aZ,0,0,1);
    Dessine_Oiseaux();
    glPopMatrix();

}

Vec3f RotY (const Vec3f & P, float a){
    Vec3f R;

    R.x = P.x * cos(a) - P.z * sin(a);
    R.z = P.x * sin(a) + P.z * cos(a);

    return R;
}

void Dessine_Vase(){
    const int N = 10; //nombre d'étages
    Vec3f P[N] = {{0,0,0},{1,1,0},{2,1.5,0},{3,2,0},{4,2.5,0},{5,3,0},{4,3.5,0},{3,4,0},{2,4.5,0},{3,5,0}}; /* forme a copier */
    Vec3f R;
    int i, j;
    float a, a2;

    for(i = 0; i < 20; i++)
    {
        a = 2 * M_PI * i / 20;
        glBegin(GL_QUADS);

        for(j = 0; j < N - 1; j++) //RotY([3],a);
        {
            a2 = 2 * M_PI * j / N;
            R = RotY(P[j], a);
            glVertex3f(R.x, R.y, R.z);
            R = RotY(P[j], a2);
            glVertex3f(R.x, R.y, R.z);
            R = RotY(P[j + 1], a2);
            glVertex3f(R.x, R.y, R.z);
            R = RotY(P[j + 1], a);
            glVertex3f(R.x, R.y, R.z);
        }
        glEnd();
    }
}

void Dessine_Arbre(int p)
{
    int a, i, nb;

    if(p < 0) return;

    glScalef(1, 0.3 * p, 1);
    draw_cylinder();
    glPushMatrix();

    nb = 1 + rand()%3;

    for(i = 0; i < nb; i++){
        a = 20 + rand() % 20;
        glRotatef(360 / nb, 0, 1, 0);
        glRotatef(a, 0, 0, 1);
    }

    glTranslatef(0, 0.3 * p, 0);
    glScalef(0.1 * p, 0.4 * p, 0.1 * p);
    Dessine_Arbre(p - 1);
    glPopMatrix();
}

void sceneInit(Scene& sc){
    animInit(sc.anim_oiseaux1, "data/anim_oiseaux_1.ani");
    animInit(sc.anim_oiseaux2, "data/anim_oiseaux_2.ani");
    animInit(sc.anim_avion, "data/anim_avion.ani");
    sc.tex_arbre = LoadGLTexture("data/billboard/arbre.ppm", true, 100, 100, 100, LOADGLTEX_GREATER);
    sc.tex_terrain = LoadGLTexture("data/terrain/terrain_new.ppm", false, 255, 255, 255, LOADGLTEX_GREATER);
    sc.tex_map = LoadGLTexture("data/cubemap/skybox_big.ppm", false, 255, 255, 255, LOADGLTEX_GREATER);
    sc.tex_aigle = LoadGLTexture("data/aigle.ppm", true, 220, 220, 220, LOADGLTEX_GREATER);
    imInitPPM(sc.terrain, "data/terrain/terrain_new_h.ppm");

}

void sceneDraw(const Scene& sc){

    srand(14);

    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    Dessine_Arbre(5);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    draw_animfly(sc.anim_avion);
    glPopMatrix();

    glBindTexture( GL_TEXTURE_2D, sc.tex_aigle);
    glEnable(GL_TEXTURE_2D);
    draw_animBird(sc.anim_oiseaux1);
    glDisable(GL_TEXTURE_2D);

    glBindTexture( GL_TEXTURE_2D, sc.tex_aigle);
    glEnable(GL_TEXTURE_2D);
    draw_animBird(sc.anim_oiseaux2);
    glDisable(GL_TEXTURE_2D);

    glBindTexture( GL_TEXTURE_2D, sc.tex_terrain);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    DessineTerrain(sc.terrain);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glBindTexture( GL_TEXTURE_2D, sc.tex_arbre);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-100,-20,-100);
    glScalef(2, 2, 2);
    dessin_foret(sc.terrain);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glBindTexture( GL_TEXTURE_2D, sc.tex_map);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0,10,0);
    glScalef(500,500,500);
    draw_cube_map();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glColor4ub(50, 150, 255, 100);
    glTranslatef(-100, -19.2, -100);
    glScalef(4.84,5,4.95);
    Dessine_eau(20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(51,38,21);
    glTranslatef(-59,-18.5,10);
    glScalef(5,3.5,3.5);
    draw_sphere();
    glPopMatrix();

    glPushMatrix();
    glColor3ub(51,38,21);
    glTranslatef(-65,-18,12);
    glScalef(3.2,3,3);
    draw_sphere();
    glPopMatrix();

    glPushMatrix();
    glColor3ub(51,38,21);
    glTranslatef(-59,-18.5,4);
    glScalef(5,3.5,3.5);
    draw_sphere();
    glPopMatrix();

    glPushMatrix();
    glColor3ub(51,38,21);
    glTranslatef(-65,-17,5);
    glScalef(3.2,3,3);
    draw_sphere();
    glPopMatrix();

    glPushMatrix();
    glColor3ub(51,38,21);
    glTranslatef(-59,-18.5,0);
    glScalef(3,2.5,2.5);
    draw_sphere();
    glPopMatrix();

    glPushMatrix();
    glColor3ub(51,38,21);
    glTranslatef(-63,-18.5,0);
    glScalef(3,2.5,2.5);
    draw_sphere();
    glPopMatrix();

    glPushMatrix();
    glColor3ub(51,38,21);
    glTranslatef(-60,-18,-3);
    glScalef(3.2,3,3);
    draw_sphere();
    glPopMatrix();
}
