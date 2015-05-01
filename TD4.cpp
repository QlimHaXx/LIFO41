//Bateaux sur l'eau l'eau...

float t = temps();
glTanslatef(0,sin(t),0);
glDisable(GL_TEXTURE_2D);
glColor(0,0,1,0.25);
glBegin(GL_QUADS);
glVertex3f(-100,0,-100);
glVertex3f(100,0,-100);
glVertex3f(-100,0,100);
glVertex3f(-100,0,-100);
glEnd();

//i se déplace selon l'axe des X et j selon l'axe des Z

float alti(int i, int j, float t, int gx, int gz)
{
    float d, z; // d distance entre le point qu'on est en train d'afficher et la goutte
    d = sqrt ((gx-i)*(gx-i)+(gz-j)*(gz-j));
    z = (cos(i*d+t)*5)/(d+1); //2 : distance entre train de vague et 5 : hauteur de +5. On peut rajouter coeff * devant d pour accélerer la vitesse

    return z;
}

void Dessine_eau(int DX, int DY) //copeir normal du terrain et remplacer avec alti
{
    float t = temps();
    int i,j;
    float z;
    int gx = 10;
    int gz = 14;
    for(i=0;i<=DX;i++)
    {
        glBegin(GL_QUAD_STRIP);
        for(j=0;j<=DY;j++)
        {
            glVertex3f(i,alti(i,j,t,dx,dz),j);
            glVertex3f(i+1,alti(i+1,j,t,dx,dz),j);
        }
        glEnd();
    }
}




// Angry bird

void Dessine_Oiseaux()
{
    float t = temps();
    glRotatef(15*cos(10*t),0,0,1);
    glBegin(GL_QUADS);
    glBegin (GL_QUADS);
    glTexCoord2f(0.5,1); //A
    glVertex3f(0,0,0); //A
    glTexCoord2f(1,1); //B
    glVertex3f(1,0,0); //B
    glTexCoord2f(1,0); //C
    glVertex3f(1,0,1); //C
    glTexCoord2f(0.5,0); //D
    glVertex3f(0,0,1); //D

    glRotatef(-15*cos(10*t),0,0,1);
    //A D E F
    glEnd();
}




//C'est la révolution (ne pas apprendre les normales pour le contrôle)



vec3f RotY (const vec3f &P, float a)
{
    vec3f R;
    R.x = P.x*cos(a) - P.z*sin(a);
    R.z = P.x*sin(a) + P.z*cos(a);
    return R;
}

void Dessine_Vase()
{
    const int N = 10; //nombre d'étages
    vect3f P[N] = {{},{},...};
    int i,j;
    Vect3f R;
    float a,a2;
    for(i=0;i<20;i++)
    {
        a = 2*M_PI*i/20;
        glBegin(GL_QUADS);
        for(j=0;j<N-1;j++) //RotY([3],a);
        {
            R = RotY(P[j],a);
            glVertex3f(R.x,R.y,R.z);
            R = RotY(P[j],a2);
            glVertex(R.x,R.Y,R.z);
            R = RotY(P[j+1],a2);
            glVertex(R.x,R.Y,R.z);
            R = RotY(P[j+1],a);
            glVertex3f(R.x,R.y,R.z);
        }
    }
}


