
#include <stdio.h>

  #include <conio.h>

  #include <graphics.h>

  #include <dos.h>



  int main() {

        /* request auto detection */

        int gdriver = DETECT, gmode, err;

        int i, j, x, y, top[2], bot[2];



        /* initialize graphic mode */

        initgraph(&gdriver, &gmode, "C:/TURBOC3/BGI");

        err = graphresult();



        if (err != grOk) {

                /* error occurred */

                printf("Graphics Error: %s",

                                grapherrormsg(err));

                return 0;

        }



        x = 75;

        y = getmaxy() / 2 - 100;



	for (i = 0; i < 10; i++) {

                /* draw the police (shooter) */

                setcolor(YELLOW);

                setlinestyle(SOLID_LINE, 1, 3);

                setfillstyle(SOLID_FILL, YELLOW);



                /* drawing head of shooter */

                circle(x, y, 15);

                floodfill(x, y, YELLOW);



                /* drawing body */

                setcolor(WHITE);

                line(x, y + 15, x, y + 80);



                /* leg design */

                line(x, y + 80, x - 25, y + 125);

                line(x, y + 80, x + 25, y + 125);



                /* hand design */

                line(x, y + 20, x - 30, y + 40);

                line(x - 30, y + 40, x - 38, y + 55);

                line(x, y + 20, x + 55, y + 5);



                /* gun design */

                rectangle(x + 45, y - 5, x + 52, y + 15);

                rectangle(x + 45, y - 5, x + 75, y + 2);

                arc(x + 52, y + 3, 270, 360, 6);

                delay(300);



                /* target */

                setcolor(YELLOW);

                setfillstyle(SOLID_FILL, YELLOW);



                /* head of target */

                circle(getmaxx() - 70, y, 15);

                floodfill(getmaxx() - 70, y, YELLOW);



                setcolor(WHITE);

                /* body of the target */

                line(getmaxx() - 70, y + 15, getmaxx() - 70, y + 80);



                /* hand  and legs target */

                line(getmaxx() - 70, y + 20, getmaxx() - 50, y + 60);

                line(getmaxx() - 70, y + 20, getmaxx() - 90, y + 60);



                line(getmaxx() - 70, y + 80, getmaxx() - 90, y + 125);

                line(getmaxx() - 70, y + 80, getmaxx() - 50, y + 125);



                top[0] = x + 78, top[1] = y - 3;

                bot[0] = x + 82, bot[1] = y;



                /* motion of bullet */

                for (j = top[0]; j < getmaxx() - 80; j = j + 10) {

                        /* draws bullet at the curren given position */

                        setcolor(LIGHTRED);

                        setfillstyle(SOLID_FILL, LIGHTRED);

                        rectangle(top[0], top[1], bot[0], bot[1]);

                        floodfill(top[0] + 1, top[1] + 1, LIGHTRED);



                        delay(10);



                        /* erase bullet at the previous position */

                        setcolor(BLACK);

                        setfillstyle(SOLID_FILL, BLACK);

                        rectangle(top[0], top[1], bot[0], bot[1]);

                        floodfill(top[0] + 1, top[1] + 1, BLACK);

                        top[0] = top[0] + 10;

                        bot[0] = bot[0] + 10;

                }



                /* bullet at the top of target */

                setcolor(LIGHTRED);

                setfillstyle(SOLID_FILL, LIGHTRED);

                rectangle(top[0] - 10, top[1], bot[0] - 10, bot[1]);

                floodfill(top[0] - 9, top[1] + 1, LIGHTRED);



                sleep(1);

                cleardevice();

        }



        getch();



        /* deallocate memory allocated for graphic screen */

        closegraph();

        return 0;

  }

