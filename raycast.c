typedef struct t_raycast
{
    int r;
    int mx;
    int my;
    int mp;
    int dof;
    int side;

    float Tan;
    float vx;
    float vy;
    float rx;
    float ry;
    float ra;
    float xo;
    float yo;
    float disV;
    float disH;
}

void raycast()
{
    r = 0;
    ra = pa;
    while (r++ < 60)
    {
        dof = 0;
        side = 0;
        distV = 100000;
        Tan=tan(ra);
        if(ra > PI)     //looking left
        {   rx = (((int)px>>6)<<6)+64;      
            ry = (px - rx) * Tan + py;
            xo = 64; 
            yo =-xo * Tan;
        }
        else if(ra < PI) //looking right
        {
            rx = (((int)px>>6)<<6) -0.0001;
            ry = (px-rx) * Tan + py;
            xo = -64;
            yo=-xo * Tan;
        }
        while(dof<8) //hit
        { 
            mx = (int)(rx)>>6;
            my = (int)(ry)>>6;
            mp = my * mapX + mx;                     
            if(mp > 0 && mp < mapX*mapY && map[mp] == 1)
            { 
                dof = 8;
                disV = cos(ra) * (rx-px)-sin(ra) * (ry-py);
            }    
            else //check next horizontal
            {
                rx += xo;
                ry += yo; 
                dof += 1;
            }
        }
    }
}