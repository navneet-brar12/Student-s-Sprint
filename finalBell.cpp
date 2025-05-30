#include <iostream>
#include <time.h>
#include <math.h>
#include "GL\glut.h"


// Define the value of PI, upto 12 decimal places
#define PI 3.141592653589

// ID to detect which scene the story is in.
int SCENE_ID;

// Variables for Animator Faders
GLfloat title_fade,
intro_next_text_appear, summary_next_text_appear,
summary_intro_fade,
kg_chap_fade, kg_title_fade,
kg_a_fade, kg_apple_fade, kg_b_fade, kg_ball_fade, kg_soon_fade, kg_subtitle_1_appear,
ps_chap_fade, ps_title_fade,
ps_subtitle_1_appear, ps_subtitle_2_appear,
hs_chap_fade, hs_title_fade,
hs_subtitle_1_appear,
puc_chap_fade, puc_title_fade,
puc_subtitle_1_fade,
eng_chap_fade, eng_title_fade,
ec_subtitle_1_fade;

// Variables for Translation Animators
GLfloat trans_x_chap1, trans_x_title1,
trans_x_chap2, trans_y_title2,
trans_x_kid1, trans_x_kid2, trans_x_kid3, trans_x_ball,
trans_subtitle_1_done, trans_subtitle_2_done,
trans_x_chap3, trans_x_title3,
trans_x_chap4, trans_x_title4,
sun_move_left,
schoolboy_x = 1150, schoolboy_y = 5220,
trans_x_sb1 = -630, trans_y_sb1 = -50, trans_x_sb2 = -1630, trans_y_sb2 = -50,
trans_x_chap5, trans_x_title5,
trans_x_ec_sb1 = 850, trans_x_ec_sb2 = -1000, trans_y_ec_sb = 40, trans_x_ec_gb = -180, trans_y_ec_gb = 1040;

// Variables for Color Morphers
GLfloat window_top_r = 59, window_top_g = 91, window_top_b = 132,
window_bottom_r = 97, window_bottom_g = 131, window_bottom_b = 159,
sky_r = 12, sky_g = 172, sky_b = 232,
grass_r = 82, grass_g = 163, grass_b = 42,
sun_r = 251, sun_g = 255, sun_b = 163;

// Variables for Turn-based Switching
bool sun_moved_half, sun_has_set, stars_are_made,
chapter_1_done, chapter_2_done, chapter_3_done, chapter_4_done, chapter_5_done, tuition_done,
puc_begin_anim, puc_end_anim,
ec_graduation_done;

// Variables for Random Star Generation
int star_alpha, no_of_stars, stars_array[40][2];

// Function to Create Delay
void delay(float secs) {
	float end = clock() / CLOCKS_PER_SEC + secs;
	while ((clock() / CLOCKS_PER_SEC) < end);
}

// Function to Print Text
void print(const char* string,
	GLfloat r, GLfloat g, GLfloat b, GLfloat a,
	GLint x, GLint y,
	GLfloat w, GLfloat h,
	GLfloat strokeSize) {
	glPushMatrix();

	glColor4f(r, g, b, a);
	glTranslatef(x, y, 0);
	glScalef(w, h, 0);

	glPointSize(strokeSize);
	glLineWidth(strokeSize);

	while (*string)
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *string++);

	glPopMatrix();

	glLineWidth(1);
	glPointSize(1);//Sets back line thickness and point size to 1 (normal)after finishing.
}

// Function to Draw Circle
void drawCircle(GLfloat x, GLfloat y,
	GLfloat r, GLfloat g, GLfloat b,
	GLfloat sx, GLfloat sy,
	GLfloat radius) {
	glPushMatrix();

	glTranslatef(x, y, 0);
	glScalef(sx, sy, 0);

	glBegin(GL_POLYGON);
	glColor3ub(r, g, b);
	for (GLfloat i = 0; i < 360; i += 5)
		glVertex2f(radius * sin(i * PI / 180), radius * cos(i * PI / 180));
	glEnd();

	glPopMatrix();
}

// Function to Draw Circle
void drawSemiCircle(GLfloat tx, GLfloat ty,
	GLfloat sx, GLfloat sy,
	GLfloat r, GLfloat g, GLfloat b,
	GLfloat radius,
	GLfloat start_angle, GLfloat end_angle) {
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glScalef(sx, sy, 0);

	glBegin(GL_POLYGON);
	glColor3ub(r, g, b);
	for (GLfloat i = start_angle; i < end_angle; i += 5)
		glVertex2f(radius * sin(i * PI / 180), radius * cos(i * PI / 180));
	glEnd();

	glPopMatrix();
}

// Function to Draw Arc
void drawArc(GLfloat tx, GLfloat ty,
	GLfloat sx, GLfloat sy,
	GLfloat r, GLfloat g, GLfloat b) {
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glScalef(sx, sy, 0);

	glPointSize(2);//Make the points(dots) a little bigger(2 pixels wide) so the arc looks nice and visible.
	glBegin(GL_POINTS);//"I am now going to draw individual points."
	glColor3ub(r, g, b);
	for (GLfloat i = 0; i < 180; i++)
		glVertex2f(-15 * cos(i * PI / 180), -15 * sin(i * PI / 180));
	glEnd();
	glPointSize(1);

	glPopMatrix();
}
// Function to Draw a Woman
void drawWoman(GLfloat tx, GLfloat ty, GLfloat sx, GLfloat sy,
	GLfloat hair_r, GLfloat hair_g, GLfloat hair_b,
	GLfloat top_r, GLfloat top_g, GLfloat top_b,
	GLfloat ribbon_r, GLfloat ribbon_g, GLfloat ribbon_b,
	GLfloat skirt_r, GLfloat skirt_g, GLfloat skirt_b) {
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glScalef(sx, sy, 0);

	// Neck
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3ub(203, 166, 108); // Darker Skin
	glVertex2f(507, 380);
	glVertex2f(507, 360);
	glVertex2f(513, 380);
	glVertex2f(513, 360);
	glEnd();
	glLineWidth(1);

	// Face
	drawCircle(510, 407,
		232, 190, 123, // Lighter Skin
		1, 1,
		30);

	// Hair
	drawSemiCircle(510, 420, 1, .6,// Because scale y = 0.6, it looks squished vertically It becomes an oval cap over the face.
		hair_r, hair_g, hair_b,
		35, -90, 90);

	drawSemiCircle(485, 400, .4, 1,//squished horizontally
		hair_r, hair_g, hair_b,
		35, -180, 0);

	// Left Eye
	drawCircle(502, 410,           // eye white
		250, 250, 250,
		1, 1,
		5);
	drawCircle(500, 408,           // pupil moved left
		10, 10, 10,
		1, 1,
		2.5);

	// Right Eye (her left eye)
	drawCircle(525, 410,
		250, 250, 250,
		1, 1,
		5);
	drawCircle(523, 408,           // pupil moved left
		10, 10, 10,
		1, 1,
		2.5);
	// Smile
	drawArc(514, 388, .5, .3,
		20, 20, 20);

	// Nose
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(515, 405);
	glVertex2f(519, 398);
	glVertex2f(519, 398);
	glVertex2f(515, 395);
	glEnd();
	glLineWidth(1);

	// Arms
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3ub(232, 190, 123); // Lighter Skin
	glVertex2f(470, 340);
	glVertex2f(470, 240);
	glVertex2f(475, 340);
	glVertex2f(475, 240);
	glVertex2f(480, 340);
	glVertex2f(480, 240);

	glVertex2f(540, 340);
	glVertex2f(540, 240);
	glVertex2f(545, 340);
	glVertex2f(545, 240);

	// Stick in Right Hand (Line pointing diagonally to board)
	glColor3ub(80, 50, 20); // Brown stick
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2f(545, 240); // From hand
	glVertex2f(580, 200); // Toward board or student's desk
	glEnd();
	glLineWidth(1);

	// Top
	glBegin(GL_POLYGON);
	glColor3ub(top_r, top_g, top_b);
	glVertex2f(460, 370);
	glVertex2f(560, 370);
	glVertex2f(540, 300);
	glVertex2f(480, 300);
	glEnd();

	// Skirt
	glBegin(GL_POLYGON);
	glColor3ub(skirt_r, skirt_g, skirt_b);
	glVertex2f(480, 300);
	glVertex2f(540, 300);
	glVertex2f(560, 180);
	glVertex2f(460, 180);
	glEnd();

	// Ribbon
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3ub(ribbon_r, ribbon_g, ribbon_b);
	glVertex2f(480, 300);
	glVertex2f(540, 300);
	glEnd();
	glLineWidth(1);

	// Legs
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3ub(232, 190, 123); // Lighter Skin
	glVertex2f(490, 180);
	glVertex2f(490, 150);
	glVertex2f(495, 180);
	glVertex2f(495, 150);

	glVertex2f(525, 180);
	glVertex2f(525, 150);
	glVertex2f(530, 180);
	glVertex2f(530, 150);
	glEnd();
	glLineWidth(1);

	glPopMatrix();
}

void drawKidsShirtAndTrousers(GLfloat tx, GLfloat ty,
	GLfloat sx, GLfloat sy,
	GLfloat shirt_r, GLfloat shirt_g, GLfloat shirt_b) {
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glScalef(sx, sy, 0);

	// Bottom Shirt
	glColor3ub(shirt_r, shirt_g, shirt_b);
	glBegin(GL_POLYGON);
	glVertex2f(0, 20);
	glVertex2f(100, 20);
	glVertex2f(100, 100);
	glVertex2f(0, 100);
	glEnd();

	// Top Shirt
	glBegin(GL_POLYGON);
	glVertex2f(100, 100);
	glVertex2f(135, 105);
	glVertex2f(120, 175);
	glVertex2f(100, 200);
	glVertex2f(50, 180);
	glVertex2f(0, 200);
	glVertex2f(-20, 175);
	glVertex2f(-35, 105);
	glVertex2f(0, 100);
	glEnd();

	// Left Trouser
	glColor3ub(37, 107, 202);
	glBegin(GL_POLYGON);
	glVertex2f(0, 25);
	glVertex2f(0, -100);
	glVertex2f(35, -100);
	glVertex2f(65, 25);
	glEnd();

	// Right Trouser
	glBegin(GL_POLYGON);
	glVertex2f(35, 25);
	glVertex2f(65, -100);
	glVertex2f(100, -100);
	glVertex2f(100, 25);
	glEnd();

	glPopMatrix();
}

void drawKid(GLfloat tx, GLfloat ty,
	GLfloat sx, GLfloat sy,
	GLfloat shirt_r, GLfloat shirt_g, GLfloat shirt_b) {
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glScalef(sx, sy, 0);

	// Neck
	drawSemiCircle(-1, -35, .6, 1,
		203, 166, 108,
		20, -90, 90);

	// Face
	drawCircle(0, 0,
		232, 190, 123,
		1, 1,
		24);

	// Left Eye
	drawCircle(-8, 0,
		250, 250, 250,
		1, 1,
		4);
	drawCircle(-6, 0,
		10, 10, 10,
		1, 1,
		2);

	// Right Eye
	drawCircle(8, 0,
		250, 250, 250,
		1, 1,
		4);
	drawCircle(10, 0,
		10, 10, 10,
		1, 1,
		2);

	// Cap
	drawSemiCircle(0, 10, 1, 1,
		37, 107, 202,
		24, -90, 90);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(20, 14);
	glVertex2f(40, 16);
	glEnd();


	// Hands
	drawCircle(-42, -82,
		232, 190, 123,
		1, 1,
		10);
	drawCircle(38, -82,
		232, 190, 123,
		1, 1,
		10);
	drawArc(0, -14, 0.4, 0.2, 0, 0, 0); // Black smile arc

	// Shirt and Trousers
	drawKidsShirtAndTrousers(-32, -125,
		.6, .5,
		shirt_r, shirt_g, shirt_b);

	// Left Shoe
	drawSemiCircle(-21, -178,
		1.2, 1,
		20, 20, 20,
		10,
		-90, 90);

	// Right Shoe
	drawSemiCircle(18, -178,
		1.2, 1,
		20, 20, 20,
		10,
		-90, 90);

	glPopMatrix();
}
void drawTree(GLfloat tx, GLfloat ty,
	GLfloat sx, GLfloat sy) {
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glScalef(sx, sy, 0);

	// Bark
	glBegin(GL_POLYGON);
	glColor3ub(86, 46, 11);
	glVertex2f(0, 0);
	glVertex2f(40, 0);
	glColor3ub(71, 36, 6);
	glVertex2f(35, 200);
	glVertex2f(5, 200);
	glEnd();

	// Tree
	drawCircle(20, 200, 5, 80, 10, 1, 1, 80);

	// Apples
	drawCircle(27, 194, 255, 0, 0, 1, 1.2, 5);
	drawCircle(-15, 170, 255, 0, 0, 1, 1.2, 5);
	drawCircle(47, 155, 255, 0, 0, 1, 1.2, 5);
	drawCircle(-2, 228, 255, 0, 0, 1, 1.2, 5);
	drawCircle(72, 216, 255, 0, 0, 1, 1.2, 5);

	glPopMatrix();
}

/*
* Scene 0 - Introduction Screen
*/
void introduction() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Story Title
	print("From Bell to Bell: Student's Sprint ",
		1, 1, 1, title_fade, 200, 380, .3, .3, 3);

	print("by Navneet(102216025)  &",
		1, 1, 1, title_fade, 790, 345, .15, .15, 1);
	print("Vartika(102216018)",
		1, 1, 1, title_fade, 840, 320, .15, .15, 1);

	print("Press N to read the story...",
		1, 1, 1, intro_next_text_appear, 560, 10, .09, .09, 1);
}

/*
* Scene 1 - Summary Screen
*/
void summary() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Summary Title
	print("Chase Your Dreams, Embrace Your Life",
		1, 1, 1, 1, 75, 650, .3, .3, 2);

	// Text: Every bell we chase...
	print("Every bell we chase, every sprint we make � shapes our journey, but remember to live it, savor the moments.",
		1, 1, 1, summary_intro_fade, 75, 590, .1, .1, 1);

	// Additional Motivational Message for balance:
	print("It's not just about the finish line, it's about enjoying the ride.",
		1, 1, 1, summary_intro_fade, 75, 550, .1, .1, 1);

	// Fade-in effect for a peaceful reminder:
	print("Pause. Breathe. Life is more than a race.",
		1, 1, 1, summary_intro_fade, 75, 510, .1, .1, 1);

	// Prompt to Proceed
	print("Press N to move on...",
		1.0, 1.0, 1.0, summary_next_text_appear,
		580, 10,
		0.09, 0.09, 1.0);
}

// Function to Draw Ceiling
void KG_drawCeiling() {
	// Ceiling
	glBegin(GL_POLYGON);
	glColor3ub(166, 148, 124); // Dark Brown
	glVertex2f(0, 800);
	glColor3ub(251, 242, 233); // Light Brown
	glVertex2f(200, 700);
	glColor3ub(251, 242, 233); // Light Brown
	glVertex2f(1400, 700);
	glColor3ub(166, 148, 124); // Dark Brown
	glVertex2f(1400, 800);
	glEnd();

	// Border for Ceiling
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0); // Black
	glVertex2f(0, 800);
	glVertex2f(200, 700);
	glVertex2f(1400, 700);
	glVertex2f(1400, 800);
	glEnd();
	glLineWidth(1);
}

// Function to Draw Side Wall
void KG_drawSideWall() {
	// Side Wall
	glBegin(GL_POLYGON);
	glColor3ub(166, 148, 124); // Dark Brown
	glVertex2f(0, 800);
	glColor3ub(251, 242, 233); // Light Brown
	glVertex2f(200, 700);
	glColor3ub(251, 242, 233); // Light Brown
	glVertex2f(200, 175);
	glColor3ub(166, 148, 124); // Dark Brown
	glVertex2f(0, 75);
	glEnd();

	// Border for Side Wall
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0); // Black
	glVertex2f(0, 800);
	glVertex2f(200, 700);
	glVertex2f(200, 175);
	glVertex2f(0, 75);
	glEnd();
	glLineWidth(1);
}

// Function to Draw Center Wall
void KG_drawCenterWall() {
	// Center Wall
	glBegin(GL_POLYGON);
	glColor3ub(251, 242, 233); // Light Brown
	glVertex2f(200, 700);
	glColor3ub(251, 242, 233); // Light Brown
	glVertex2f(1400, 700);
	glColor3ub(166, 148, 124); // Dark Brown
	glVertex2f(1400, 175);
	glColor3ub(166, 148, 124); // Dark Brown
	glVertex2f(200, 175);
	glEnd();

	// Border for Center Wall
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0); // Black
	glVertex2f(200, 700);
	glVertex2f(1400, 700);
	glVertex2f(1400, 175);
	glVertex2f(200, 175);
	glEnd();
	glLineWidth(1);

	// Left Chart - Lowered and Wider
	glBegin(GL_POLYGON);
	glColor3ub(255, 255, 255); // White Chart
	glVertex2f(240, 550);
	glVertex2f(420, 550);
	glVertex2f(420, 350);
	glVertex2f(240, 350);
	glEnd();

	// Border
	glLineWidth(4);
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0);
	glVertex2f(240, 550);
	glVertex2f(420, 550);
	glVertex2f(420, 350);
	glVertex2f(240, 350);
	glEnd();
	// Right Chart - Lowered and Wider
	glBegin(GL_POLYGON);
	glColor3ub(255, 255, 255); // White Chart
	glVertex2f(1140, 550);
	glVertex2f(1360, 550);
	glVertex2f(1360, 350);
	glVertex2f(1140, 350);
	glEnd();

	// Border
	glLineWidth(4);
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0); // Black border
	glVertex2f(1140, 550);
	glVertex2f(1360, 550);
	glVertex2f(1360, 350);
	glVertex2f(1140, 350);
	glEnd();


	// Sky (upper half of chart)
	glBegin(GL_POLYGON);
	glColor3ub(173, 216, 230); // Light Blue
	glVertex2f(240, 550);
	glVertex2f(420, 550);
	glVertex2f(420, 460);
	glVertex2f(240, 460);
	glEnd();

	// Grass (lower half of chart)
	glBegin(GL_POLYGON);
	glColor3ub(34, 139, 34); // Cornflower Blue (bluish grass)
	glVertex2f(240, 460);
	glVertex2f(420, 460);
	glVertex2f(420, 350);
	glVertex2f(240, 350);
	glEnd();

	// Hut base
	glBegin(GL_POLYGON);
	glColor3ub(210, 180, 140); // Tan
	glVertex2f(290, 430);
	glVertex2f(370, 430);
	glVertex2f(370, 390);
	glVertex2f(290, 390);
	glEnd();

	// Hut roof
	glBegin(GL_TRIANGLES);
	glColor3ub(139, 69, 19); // SaddleBrown
	glVertex2f(280, 430);
	glVertex2f(380, 430);
	glVertex2f(330, 460);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(173, 216, 230); // Light blue
	glVertex2f(1140, 550);
	glVertex2f(1360, 550);
	glVertex2f(1360, 350);
	glVertex2f(1140, 350);
	glEnd();

	// Sun
	drawCircle(1320, 520, 255, 223, 0, 1.0f, 1.0f, 15); // Sun in yellow

	// Ground
	glBegin(GL_POLYGON);
	glColor3ub(124, 252, 0); // Lawn green
	glVertex2f(1140, 400);
	glVertex2f(1360, 400);
	glVertex2f(1360, 350);
	glVertex2f(1140, 350);
	glEnd();

	// Hut base - Purple
	glBegin(GL_POLYGON);
	glColor3ub(128, 0, 128); // Purple
	glVertex2f(1200, 400);
	glVertex2f(1200, 450);
	glVertex2f(1260, 450);
	glVertex2f(1260, 400);
	glEnd();

	// Hut roof - Darker purple triangle
	glBegin(GL_TRIANGLES);
	glColor3ub(75, 0, 130); // Indigo
	glVertex2f(1180, 450);
	glVertex2f(1230, 490);
	glVertex2f(1280, 450);
	glEnd();


}


// Function to Draw Floor
void KG_drawFloor() {
	// Floor
	glBegin(GL_POLYGON);
	glColor3ub(166, 148, 124); // Dark Brown
	glVertex2f(200, 175);
	glVertex2f(1400, 175);
	glVertex2f(1400, 75);
	glVertex2f(0, 75);
	glEnd();

	// Border for Floor
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0); // Black
	glVertex2f(200, 175);
	glVertex2f(1400, 175);
	glVertex2f(1400, 75);
	glVertex2f(0, 75);
	glEnd();
	glLineWidth(1);
}

// Function to Draw Door
void KG_drawDoor() {
	// Door Hinges
	glLineWidth(6);
	glBegin(GL_LINE_LOOP);
	glColor3ub(63, 36, 19); // Chocolate Brown
	glVertex2f(0, 600);
	glVertex2f(180, 540);
	glVertex2f(180, 165);
	glVertex2f(0, 75);
	glEnd();
	glLineWidth(1);

	// Door
	glBegin(GL_POLYGON);
	glColor3ub(63, 36, 19); // Chocolate Brown
	glVertex2f(0, 600);
	glVertex2f(180, 540);
	glVertex2f(180, 165);
	glVertex2f(0, 75);
	glEnd();

	// Door Knob
	drawCircle(160, 350,
		223, 189, 31, // Goldish Yellow
		1, 1,
		8);
}

// Function to Draw Kid's Head
void KG_drawKidsHead(GLfloat tx, GLfloat ty) {
	glPushMatrix();

	glTranslatef(tx, ty, 0);

	// Kid's Face
	drawCircle(480, 110,
		232, 190, 123, // Lighter Skin
		1, 1,
		25);

	int hair_line;

	// Kid's Hair Strands
	hair_line = 400;
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3ub(20, 20, 20); // Almost Black
	glVertex2f(hair_line + 60, 138);
	glVertex2f(hair_line + 65, 128);

	glVertex2f(hair_line + 70, 140);
	glVertex2f(hair_line + 75, 130);

	glVertex2f(hair_line + 80, 140);
	glVertex2f(hair_line + 85, 130);

	glVertex2f(hair_line + 90, 138);
	glVertex2f(hair_line + 95, 128);
	glEnd();
	glLineWidth(1);
	drawSemiCircle(480, 85, 1, 0.6,   // Position below the face
		255, 0, 0, // Dark Brown shirt color
		25, -90, 90); // 25 radius, 180 to 0 to form the bottom half

	glPopMatrix();
}

// Function to Draw Blackboard
void KG_drawBlackboard() {
	// Blackboard
	glBegin(GL_POLYGON);
	glColor3ub(20, 20, 20); // Almost Black
	glVertex2f(450, 540);
	glVertex2f(1100, 540);
	glVertex2f(1100, 300);
	glVertex2f(450, 300);
	glEnd();

	// Blackboard Border
	glLineWidth(10);
	glBegin(GL_LINE_LOOP);
	glColor3ub(63, 36, 19); // Chocolate Brown
	glVertex2f(450, 540);
	glVertex2f(1100, 540);
	glVertex2f(1100, 300);
	glVertex2f(450, 300);
	glEnd();
	glLineWidth(1);
}

// Function to Draw Teacher's Table
void KG_drawTeachersTable() {
	// Teacher's Table
	glBegin(GL_POLYGON);
	glColor3ub(63, 36, 19); // Chocolate Brown
	glVertex2f(510, 260);
	glVertex2f(470, 200);
	glVertex2f(1080, 200);
	glVertex2f(1040, 260);
	glEnd();

	// Teacher's Table Edge
	glBegin(GL_POLYGON);
	glColor3ub(54, 28, 16); // Darker Chocolate Brown
	glVertex2f(470, 200);
	glVertex2f(470, 190);
	glVertex2f(1080, 190);
	glVertex2f(1080, 200);
	glEnd();

	// Left Table Leg
	glBegin(GL_POLYGON);
	glColor3ub(54, 28, 16); // Darker Chocolate Brown
	glVertex2f(530, 190);
	glVertex2f(540, 190);
	glVertex2f(540, 130);
	glVertex2f(530, 130);
	glEnd();

	// Right Table Leg
	glBegin(GL_POLYGON);
	glColor3ub(54, 28, 16); // Darker Chocolate Brown
	glVertex2f(1020, 190);
	glVertex2f(1010, 190);
	glVertex2f(1010, 130);
	glVertex2f(1020, 130);
	glEnd();
}
void KG_drawBooksOnTable() {
	// Book 1 - Red Book
	glBegin(GL_POLYGON);
	glColor3ub(178, 34, 34); // Firebrick Red
	glVertex2f(600, 240);
	glVertex2f(600, 215);
	glVertex2f(680, 215);
	glVertex2f(680, 240);
	glEnd();

	// Book 2 - Blue Book (slightly rotated/offset for variety)
	glBegin(GL_POLYGON);
	glColor3ub(25, 25, 112); // Midnight Blue
	glVertex2f(700, 235);
	glVertex2f(695, 210);
	glVertex2f(765, 210);
	glVertex2f(770, 235);
	glEnd();
}

// Function to Draw Children's Desks
void KG_drawChildrensDesks() {
	// Left Children's Desk
	glBegin(GL_POLYGON);
	glColor3ub(138, 82, 32); // Wood Brown
	glVertex2f(400, 150);
	glVertex2f(700, 150);
	glVertex2f(730, 120);
	glVertex2f(370, 120);
	glEnd();

	// Left Children's Desk Edge
	glBegin(GL_POLYGON);
	glColor3ub(122, 76, 29); // Wood Dark Brown
	glVertex2f(370, 120);
	glVertex2f(370, 115);
	glVertex2f(730, 115);
	glVertex2f(730, 120);
	glEnd();

	// Right Children's Desk
	glBegin(GL_POLYGON);
	glColor3ub(138, 82, 32); // Wood Brown
	glVertex2f(850, 150);
	glVertex2f(1150, 150);
	glVertex2f(1180, 120);
	glVertex2f(820, 120);
	glEnd();

	// Right Children's Desk Edge
	glBegin(GL_POLYGON);
	glColor3ub(122, 76, 29); // Wood Dark Brown
	glVertex2f(820, 120);
	glVertex2f(820, 115);
	glVertex2f(1180, 115);
	glVertex2f(1180, 120);
	glEnd();
}

/*
* Scene 2 - Kindergarten Title Screen
*/
void kindergartenTitleScreen() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Story Title
	print("CHAPTER 1",
		1, 1, 1, kg_chap_fade, 300 + trans_x_chap1, 400, .2, .2, 2);
	print("Kindergarten",
		1, 1, 1, kg_title_fade, 300 + trans_x_title1, 350, .3, .3, 2);
}

/*
* Scene 3 - Kindergarten
*/
void kindergarten() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	KG_drawCeiling();
	KG_drawSideWall();
	KG_drawCenterWall();
	KG_drawFloor();


	KG_drawDoor();

	KG_drawBlackboard();

	drawWoman(500, 0, 1, 1,
		60, 60, 60,      // hair color (keep dark)
		135, 206, 250,   // top (light sky blue)
		255, 105, 180,   // ribbon (hot pink)
		72, 61, 139      // skirt (dark slate blue)
	);


	KG_drawTeachersTable();
	KG_drawBooksOnTable();
	KG_drawChildrensDesks();

	KG_drawKidsHead(0, 0);
	KG_drawKidsHead(140, 0);
	KG_drawKidsHead(460, 0);
	KG_drawKidsHead(600, 0);

	print("A, B, C, D, E, ",
		1, 1, 1, kg_a_fade, 500, 440, .3, .3, 3);



	print("F, G, H, I ... ",
		1, 1, 1, kg_b_fade, 500, 350, .3, .3, 3);


	print("This is where our educational journey begins...",
		1, 1, 1, kg_subtitle_1_appear, 380, 30, .14, .14, 1);
}

/*
*	Scene 4 - Primary School Title Screen
*/
void primarySchoolTitleScreen() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Story Title
	print("CHAPTER 2",
		1, 1, 1, ps_chap_fade, 300 + trans_x_chap2, 400, .2, .2, 2);
	print("Primary School",
		1, 1, 1, ps_title_fade, 400, 250 + trans_y_title2, .3, .3, 2);
}

// Function to Draw Ceiling
void PS_drawCeiling() {
	// Ceiling
	glBegin(GL_POLYGON);
	glColor3ub(65, 105, 120); // Aqua
	glVertex2f(0, 800);
	glVertex2f(0, 700);
	glVertex2f(100, 650);
	glVertex2f(1400, 650);
	glVertex2f(1400, 800);
	glEnd();

	// Border for Ceiling
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0);
	glVertex2f(0, 800);
	glVertex2f(0, 700);
	glVertex2f(100, 650);
	glVertex2f(1400, 650);
	glVertex2f(1400, 800);
	glEnd();
}

// Function to Draw Side Wall
void PS_drawSideWall() {
	// Side Wall
	glBegin(GL_POLYGON);
	glColor3ub(176, 204, 217); // Light Aqua
	glVertex2f(0, 700);
	glVertex2f(100, 650);
	glVertex2f(100, 200);
	glVertex2f(0, 75);
	glEnd();

	// Border for Side Wall
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0);
	glVertex2f(0, 700);
	glVertex2f(100, 650);
	glVertex2f(100, 200);
	glVertex2f(0, 75);
	glEnd();


	// Outer frame (perspective-corrected)
	glColor3ub(60, 30, 10); // Dark brown frame
	glBegin(GL_POLYGON);
	glVertex2f(25, 530);  // Top-left
	glVertex2f(90, 505);  // Top-right (angled lower)
	glVertex2f(90, 445);  // Bottom-right
	glVertex2f(25, 470);  // Bottom-left
	glEnd();

	// Inner photo area (also skewed)
	glColor3ub(255, 228, 196); // Light beige photo
	glBegin(GL_POLYGON);
	glVertex2f(35, 520);  // Top-left
	glVertex2f(80, 500);  // Top-right
	glVertex2f(80, 455);  // Bottom-right
	glVertex2f(35, 475);  // Bottom-left
	glEnd();
	// Sun face (centered within the photo)
	drawCircle(58, 488, 255, 204, 0, 1, 1, 10); // Yellow sun


}
// Function to Draw Center Wall
void PS_drawCenterWall() {
	// Center Wall
	glBegin(GL_POLYGON);
	glColor3ub(120, 160, 175);
	glVertex2f(100, 650);
	glVertex2f(700, 650);
	glColor3ub(164, 191, 203);
	glVertex2f(700, 200);
	glVertex2f(100, 200);
	glEnd();

	// Border for Center Wall
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0);
	glVertex2f(100, 650);
	glVertex2f(700, 650);
	glVertex2f(700, 200);
	glVertex2f(100, 200);
	glEnd();

	drawCircle(600, 600, 0, 0, 0, 1.4, 1.1, 30); // Position adjusted to center on the wall

	// Inner white clock face
	drawCircle(600, 600, 255, 255, 255, 1.2, 1.0, 27);

	// Clock hands
	glLineWidth(2);
	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(600, 600);     // Center
	glVertex2f(620, 600);     // Hour hand (12 o'clock)
	glVertex2f(600, 600);     // Center again
	glVertex2f(600, 620);     // Minute hand (3 o'clock)
	glEnd();
	glLineWidth(1);
}

// Function to Draw Dividing Wall
void PS_drawDividingWall() {
	// Dividing Wall
	glBegin(GL_POLYGON);
	glColor3ub(176, 204, 217); // Light Aqua
	glVertex2f(700, 650);
	glVertex2f(850, 800);
	glVertex2f(850, 75);
	glVertex2f(700, 200);
	glEnd();

	// Border for Dividing Wall
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0);
	glVertex2f(700, 650);
	glVertex2f(850, 800);
	glVertex2f(850, 75);
	glVertex2f(700, 200);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(139, 69, 19);
	glVertex2f(725, 625);       // Top-left corner (inward from the wall)
	glVertex2f(800, 705); // Top-right corner

	glVertex2f(800, 105);       // Bottom-right corner

	glVertex2f(725, 175);       // Bottom-left corner
	glEnd();


	glLineWidth(4);
	glBegin(GL_LINE_LOOP);

	glColor3ub(101, 67, 33);
	glVertex2f(725, 625);
	glVertex2f(800, 705);
	glVertex2f(800, 105);
	glVertex2f(725, 175);
	glEnd();
	glLineWidth(1);

	drawCircle(780, 400, 225, 255, 0, 1.0, 1.0, 10);  // Use sx = sy = 1.0 for no scaling



}



// Function to Draw Kitchen Wall
void PS_drawKitchenWall() {
	// Kitchen Wall
	glBegin(GL_POLYGON);
	glColor3ub(164, 191, 203);
	glVertex2f(850, 800);
	glVertex2f(1400, 800);
	glVertex2f(1400, 75);
	glVertex2f(850, 75);
	glEnd();

	// Border for Kitchen Wall
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0);
	glVertex2f(850, 800);
	glVertex2f(1400, 800);
	glVertex2f(1400, 75);
	glVertex2f(850, 75);
	glEnd();



}

// Function to Draw Floor
void PS_drawFloor() {
	// Floor
	glBegin(GL_POLYGON);
	glColor3ub(120, 160, 175);
	glVertex2f(100, 200);
	glVertex2f(700, 200);
	glVertex2f(850, 75);
	glVertex2f(0, 75);
	glEnd();

	// Border for Floor
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0);
	glVertex2f(100, 200);
	glVertex2f(700, 200);
	glVertex2f(850, 75);
	glVertex2f(0, 75);
	glEnd();
}

// Function to Draw Door
void PS_drawDoor() {
	// Door
	glBegin(GL_POLYGON);
	glColor3ub(255, 255, 255);
	glVertex2f(300, 500);
	glVertex2f(500, 500);
	glVertex2f(500, 200);
	glVertex2f(300, 200);
	glEnd();

	// Border
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3ub(122, 76, 29); // Wood Dark Brown
	glVertex2f(300, 200);
	glVertex2f(300, 500);
	glVertex2f(300, 500);
	glVertex2f(500, 500);
	glVertex2f(500, 500);
	glVertex2f(500, 200);
	glEnd();
	glLineWidth(1);
}

void PS_drawBackground() {
	glBegin(GL_POLYGON);
	glColor3ub(12, 172, 232); // Sky Blue
	glVertex2f(300, 500);
	glVertex2f(500, 500);
	glColor3ub(82, 163, 42); // Green Grass
	glVertex2f(500, 275);
	glVertex2f(300, 275);
	glEnd();
}

void PS_drawRoad() {
	glBegin(GL_POLYGON);
	glColor3ub(40, 40, 40);
	glVertex2f(300, 275);
	glVertex2f(500, 275);
	glVertex2f(500, 200);
	glVertex2f(300, 200);
	glEnd();

	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3ub(255, 255, 255);
	glVertex2f(300, 235);
	glVertex2f(380, 235);
	glVertex2f(420, 235);
	glVertex2f(500, 235);
	glEnd();
	glLineWidth(1);
}

void PS_drawOutside() {
	PS_drawBackground();
	PS_drawRoad();
}

void PS_drawKitchenCounter() {
	// Kitchen Counter
	glBegin(GL_POLYGON);
	glColor3ub(138, 82, 32); //Wood Brown
	glVertex2f(950, 300);
	glVertex2f(980, 325);
	glVertex2f(1300, 325);
	glVertex2f(1300, 300);
	glEnd();

}

void PS_drawKitchen() {
	glBegin(GL_POLYGON);
	glColor3ub(247, 239, 187);
	glVertex2f(950, 550);
	glVertex2f(1300, 550);
	glVertex2f(1300, 300);
	glVertex2f(950, 300);
	glEnd();

	glLineWidth(4); // Make the border thicker
	glBegin(GL_LINES);
	glColor3ub(30, 60, 150); // Darker brown for visible border
	glVertex2f(950, 300);
	glVertex2f(950, 550);
	glVertex2f(950, 550);
	glVertex2f(1300, 550);
	glVertex2f(1300, 550);
	glVertex2f(1300, 300);
	glEnd();
	glLineWidth(1); // Reset line width


	// Mother
	drawWoman(1630, 50, -1, 1,
		20, 20, 20,
		229, 49, 49, // top
		37, 107, 202, // bottom
		229, 49, 49 // skirt
	);

	// Hack to Hide Woman's Body
	glBegin(GL_POLYGON);
	glColor3ub(164, 191, 203);
	glVertex2f(1050, 300);
	glVertex2f(1200, 300);
	glVertex2f(1200, 140);
	glVertex2f(1050, 140);
	glEnd();

	// Kitchen Table
	glBegin(GL_POLYGON);
	glColor3ub(138, 82, 32);
	glVertex2f(950, 300);
	glVertex2f(1000, 330);
	glVertex2f(1300, 330);
	glVertex2f(1300, 300);
	glEnd();
}
/*
*	Scene 5 - Primary School
*/
void primarySchool() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	print("KID: Mom, can I go outside and play football with my friends?",
		1, 1, 1, ps_subtitle_1_appear, 300, 30 + trans_subtitle_1_done, .14, .14, 1);

	print("MOM: First finish your homework, dear.There will always be time to play � once your work is done.",
		1, 1, 1, ps_subtitle_2_appear, 100, 30 + trans_subtitle_2_done, .12, .12, 1);

	PS_drawCeiling();
	PS_drawSideWall();
	PS_drawCenterWall();
	PS_drawDividingWall();
	PS_drawFloor();


	PS_drawDoor();

	PS_drawOutside();

	PS_drawKitchenWall();
	PS_drawKitchen();

	// Kids inside House
	drawKid(250, 370,
		1, 1,
		255, 0, 0);

	// Back Kid
	drawKid(360 + trans_x_kid1, 380,
		-.3, .3,
		80, 50, 20);

	// Left Kid
	drawKid(350 + trans_x_kid2, 350,
		.3, .3,
		255, 255, 0);

	// Right Kid
	drawKid(400 + trans_x_kid3, 350,
		-.3, .3,
		255, 50, 0);

	// Ball
	drawCircle(380 + trans_x_ball, 305,
		200, 200, 200,
		1, 1,
		6);
}

/*
*	Scene 6 - High School Title Screen
*/
void highSchoolTitleScreen() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Story Title
	print("CHAPTER 3",
		1, 1, 1, hs_chap_fade, 300 + trans_x_chap3, 400, .2, .2, 2);
	print("High School",
		1, 1, 1, hs_title_fade, 400 - trans_x_title3, 350, .3, .3, 2);
}

void HS_drawBackground() {
	// Background
	glBegin(GL_POLYGON);
	glColor3ub(sky_r, sky_g, sky_b); // Sky Blue
	glVertex2f(0, 800);
	glVertex2f(1400, 800);
	glVertex2f(1400, 400);
	glVertex2f(0, 400);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(sky_r, sky_g, sky_b); // Sky Blue
	glVertex2f(0, 400);
	glVertex2f(1400, 400);
	glColor3ub(grass_r, grass_g, grass_b); // Green Grass
	glVertex2f(1400, 175);
	glVertex2f(0, 175);
	glEnd();
}

void HS_drawSun() {
	// Sun
	drawCircle(1250 - sun_move_left, 700,
		sun_r, sun_g, sun_b,
		1, 1,
		50);
}

void HS_drawRoad() {
	// Road
	glBegin(GL_POLYGON);
	glColor3ub(40, 40, 40);
	glVertex2f(0, 175);
	glVertex2f(1400, 175);
	glVertex2f(1400, 75);
	glVertex2f(0, 75);
	glEnd();

	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3ub(255, 255, 255);
	glVertex2f(0, 125);
	glVertex2f(200, 125);

	glVertex2f(300, 125);
	glVertex2f(500, 125);

	glVertex2f(600, 125);
	glVertex2f(800, 125);

	glVertex2f(900, 125);
	glVertex2f(1100, 125);

	glVertex2f(1200, 125);
	glVertex2f(1400, 125);
	glEnd();
	glLineWidth(1);
}

void HS_drawHome() {
	// Home Bottom
	glBegin(GL_POLYGON);
	glColor3ub(169, 117, 83);
	glVertex2f(1375, 175);
	glColor3ub(181, 145, 113);
	glVertex2f(1375, 300);
	glColor3ub(181, 145, 113);
	glVertex2f(1100, 300);
	glColor3ub(169, 117, 83);
	glVertex2f(1100, 175);
	glEnd();

	// Home Bottom Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(1375, 175);
	glVertex2f(1375, 300);
	glVertex2f(1100, 300);
	glVertex2f(1100, 175);
	glEnd();

	// Home Top Left
	glBegin(GL_POLYGON);
	glColor3ub(181, 145, 113);
	glVertex2f(1100, 300);
	glVertex2f(1220, 300);
	glColor3ub(169, 117, 83);
	glVertex2f(1220, 400);
	glVertex2f(1100, 400);
	glEnd();

	// Home Top Left Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(1100, 300);
	glVertex2f(1220, 300);
	glVertex2f(1220, 400);
	glVertex2f(1100, 400);
	glEnd();

	// Triangle Rooftop
	glBegin(GL_TRIANGLES);
	glColor3ub(69, 39, 23);
	glVertex2f(1090, 400);
	glVertex2f(1230, 400);
	glVertex2f(1160, 450);
	glEnd();

	// Triangle Rooftop Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(1090, 400);
	glVertex2f(1230, 400);
	glVertex2f(1160, 450);
	glEnd();

	// Home Top Right
	glBegin(GL_POLYGON);
	glColor3ub(69, 39, 23);
	glVertex2f(1220, 375);
	glVertex2f(1375, 375);
	glVertex2f(1375, 300);
	glVertex2f(1220, 300);
	glEnd();

	glBegin(GL_LINES);
	glColor3ub(99, 56, 33);
	for (int temp_x = 1220; temp_x <= 1375; temp_x += 5) {
		glVertex2f(temp_x, 375);
		glVertex2f(temp_x, 300);
	}
	for (int temp_y = 300; temp_y <= 375; temp_y += 5) {
		glVertex2f(1220, temp_y);
		glVertex2f(1375, temp_y);
	}
	glEnd();

	// Home Bottom-Top Divider
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3ub(20, 20, 20);
	glVertex2f(1090, 300);
	glVertex2f(1385, 300);
	glEnd();
	glLineWidth(1);

	// Door
	glBegin(GL_POLYGON);
	glColor3ub(31, 47, 53);
	glVertex2f(1130, 175);
	glVertex2f(1130, 280);
	glVertex2f(1190, 280);
	glVertex2f(1190, 175);
	glEnd();

	// Door Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(1130, 175);
	glVertex2f(1130, 280);
	glVertex2f(1190, 280);
	glVertex2f(1190, 175);
	glEnd();

	// Top Window
	glBegin(GL_POLYGON);
	glColor3ub(window_top_r, window_top_g, window_top_b);
	glVertex2f(1130, 330);
	glVertex2f(1130, 370);
	glVertex2f(1190, 370);
	glColor3ub(window_bottom_r, window_bottom_g, window_bottom_b);
	glVertex2f(1190, 330);
	glEnd();

	// Top Window Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(1130, 330);
	glVertex2f(1130, 370);
	glVertex2f(1190, 370);
	glVertex2f(1190, 330);
	glEnd();

	// Rectangular Window
	glBegin(GL_POLYGON);
	glColor3ub(59, 91, 132);
	glVertex2f(1240, 280);
	glVertex2f(1240, 240);
	glVertex2f(1355, 240);
	glColor3ub(97, 131, 159);
	glVertex2f(1355, 280);
	glEnd();

	// Rectangular Window Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(1240, 280);
	glVertex2f(1240, 240);
	glVertex2f(1355, 240);
	glVertex2f(1355, 280);
	glEnd();

	// Rectangular Window Panes
	glBegin(GL_LINES);
	glColor3ub(20, 20, 20);
	glVertex2f(1297, 280);
	glVertex2f(1297, 240);
	glVertex2f(1355, 260);
	glVertex2f(1240, 260);
	glEnd();

	// Top Circle
	drawCircle(1160, 420,
		255, 255, 255,
		1, 1,
		10);
}
void HS_drawSchool() {
	// School Building
	glBegin(GL_POLYGON);
	glColor3ub(184, 88, 68);
	glVertex2f(400, 175);
	glVertex2f(1000, 175);
	glVertex2f(1000, 500);
	glColor3ub(241, 130, 94);
	glVertex2f(400, 500);
	glEnd();

	// School Building Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(400, 175);
	glVertex2f(1000, 175);
	glVertex2f(1000, 500);
	glVertex2f(400, 500);
	glEnd();

	// School Board
	glBegin(GL_POLYGON);
	glColor3ub(183, 184, 188);
	glVertex2f(570, 530);
	glVertex2f(830, 530);
	glVertex2f(830, 470);
	glVertex2f(570, 470);
	glEnd();

	// School Board Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(570, 530);
	glVertex2f(830, 530);
	glVertex2f(830, 470);
	glVertex2f(570, 470);
	glEnd();

	print("SCHOOL", 0, 0, 0, 1, 610, 485, .3, .3, 1.5);

	// School Door
	glBegin(GL_POLYGON);
	glColor3ub(183, 184, 188);
	glVertex2f(600, 175);
	glVertex2f(600, 280);
	glVertex2f(800, 280);
	glVertex2f(800, 175);
	glEnd();

	// School Door Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(600, 175);
	glVertex2f(600, 280);
	glVertex2f(800, 280);
	glVertex2f(800, 175);
	glEnd();

	// School Door Divider
	glBegin(GL_LINES);
	glColor3ub(20, 20, 20);
	glVertex2f(700, 280);
	glVertex2f(700, 175);
	glEnd();

	// School Windows
	for (int i = 0; i <= 500; i += 100) {
		for (int j = 0; j <= 100; j += 80) {
			glBegin(GL_POLYGON);
			glColor3ub(59, 91, 132);
			glVertex2f(425 + i, 450 - j);
			glVertex2f(475 + i, 450 - j);
			glVertex2f(475 + i, 400 - j);
			glColor3ub(97, 131, 159);
			glVertex2f(425 + i, 400 - j);
			glEnd();

			glBegin(GL_LINE_LOOP);
			glColor3ub(20, 20, 20);
			glVertex2f(425 + i, 450 - j);
			glVertex2f(475 + i, 450 - j);
			glVertex2f(475 + i, 400 - j);
			glVertex2f(425 + i, 400 - j);
			glEnd();

			glLineWidth(4);
			glBegin(GL_LINES);
			glColor3ub(140, 75, 55);
			glVertex2f(425 + i, 400 - j);
			glVertex2f(475 + i, 400 - j);
			glEnd();
			glLineWidth(1);
		}
	}

	glBegin(GL_POLYGON);
	glColor3ub(59, 91, 132);
	glVertex2f(425, 280);
	glVertex2f(475, 280);
	glVertex2f(475, 200);
	glColor3ub(97, 131, 159);
	glVertex2f(425, 200);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(425, 280);
	glVertex2f(475, 280);
	glVertex2f(475, 200);
	glVertex2f(425, 200);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(59, 91, 132);
	glVertex2f(525, 280);
	glVertex2f(575, 280);
	glVertex2f(575, 200);
	glColor3ub(97, 131, 159);
	glVertex2f(525, 200);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(525, 280);
	glVertex2f(575, 280);
	glVertex2f(575, 200);
	glVertex2f(525, 200);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(59, 91, 132);
	glVertex2f(825, 280);
	glVertex2f(875, 280);
	glVertex2f(875, 200);
	glColor3ub(97, 131, 159);
	glVertex2f(825, 200);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(825, 280);
	glVertex2f(875, 280);
	glVertex2f(875, 200);
	glVertex2f(825, 200);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(59, 91, 132);
	glVertex2f(925, 280);
	glVertex2f(975, 280);
	glVertex2f(975, 200);
	glColor3ub(97, 131, 159);
	glVertex2f(925, 200);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(925, 280);
	glVertex2f(975, 280);
	glVertex2f(975, 200);
	glVertex2f(925, 200);
	glEnd();
}

void HS_drawTuition() {
	// Tuition Building
	glBegin(GL_POLYGON);
	glColor3ub(151, 188, 207);
	glVertex2f(25, 175);
	glVertex2f(300, 175);
	glColor3ub(144, 180, 200);
	glVertex2f(300, 350);
	glVertex2f(25, 350);
	glEnd();

	// Tuition Building Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(25, 175);
	glVertex2f(300, 175);
	glVertex2f(300, 350);
	glVertex2f(25, 350);
	glEnd();

	// Tuition Board
	glBegin(GL_POLYGON);
	glColor3ub(255, 218, 154);
	glVertex2f(50, 375);
	glVertex2f(180, 375);
	glVertex2f(180, 325);
	glVertex2f(50, 325);
	glEnd();

	// Tuition Board Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(50, 375);
	glVertex2f(180, 375);
	glVertex2f(180, 325);
	glVertex2f(50, 325);
	glEnd();

	print("TUITION", 0, 0, 0, 1, 58, 342, .15, .15, 1.3);

	// Tuition Door
	glBegin(GL_POLYGON);
	glColor3ub(70, 39, 21);
	glVertex2f(55, 175);
	glVertex2f(55, 280);
	glVertex2f(115, 280);
	glVertex2f(115, 175);
	glEnd();

	// Tuition Door Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(55, 175);
	glVertex2f(55, 280);
	glVertex2f(115, 280);
	glVertex2f(115, 175);
	glEnd();

	// Tuition Rectangular Window
	glBegin(GL_POLYGON);
	glColor3ub(59, 91, 132);
	glVertex2f(155, 280);
	glVertex2f(155, 240);
	glVertex2f(270, 240);
	glColor3ub(97, 131, 159);
	glVertex2f(270, 280);
	glEnd();

	// Tuition Rectangular Window Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(155, 280);
	glVertex2f(155, 240);
	glVertex2f(270, 240);
	glVertex2f(270, 280);
	glEnd();

	// Tuition Rectangular Window Panes
	glBegin(GL_LINES);
	glColor3ub(20, 20, 20);
	glVertex2f(213, 280);
	glVertex2f(213, 240);
	glVertex2f(155, 260);
	glVertex2f(270, 260);
	glEnd();
}

void HS_drawLights() {
	// Left Light Pole
	glLineWidth(4);
	glBegin(GL_LINES);
	glColor3ub(200, 200, 200);
	glVertex2f(350, 175);
	glVertex2f(350, 300);
	glEnd();
	glLineWidth(1);

	// Right Light Pole
	glLineWidth(4);
	glBegin(GL_LINES);
	glColor3ub(200, 200, 200);
	glVertex2f(1050, 175);
	glVertex2f(1050, 300);
	glEnd();
	glLineWidth(1);

	// Left Bulb
	drawCircle(350, 300,
		window_top_r, window_top_g, window_top_b,
		1, 1,
		15);

	// Right Bulb
	drawCircle(1050, 300,
		window_top_r, window_top_g, window_top_b,
		1, 1,
		15);
}

void HS_drawStars() {
	if (stars_are_made == false) {
		for (int i = 0, j = 0; i < 40; i++) {
			stars_array[i][j] = 0 + (rand() % (int)(1400 - 0 + 1));
			stars_array[i][j + 1] = 530 + (rand() % (int)(800 - 530 + 1));
			no_of_stars++;
		}
		stars_are_made = true;
	}
	else {
		glPointSize(2);
		glBegin(GL_POINTS);
		glColor4ub(255, 255, 255, star_alpha);
		for (int i = 0, j = 0; i < no_of_stars; i++)
			glVertex2f(stars_array[i][j], stars_array[i][j + 1]);
		glEnd();
		glPointSize(1);
	}
}

void drawSchoolBoy(GLfloat tx, GLfloat ty,
	GLfloat sx, GLfloat sy,
	GLfloat shirt_r, GLfloat shirt_g, GLfloat shirt_b) {
	glPushMatrix();

	glScalef(sx, sy, 0);
	glTranslatef(tx, ty, 0);

	// Shoes
	drawSemiCircle(1160, 120,
		1, 1,
		255, 255, 255,
		10,
		-90, 91);

	// Shoe Extension
	glBegin(GL_POLYGON);
	glColor3ub(255, 255, 255);
	glVertex2f(1160, 120);
	glVertex2f(1170, 120);
	glVertex2f(1170, 135);
	glVertex2f(1160, 135);
	glEnd();

	// Pants
	glBegin(GL_POLYGON);
	glColor3ub(0, 0, 200);
	glVertex2f(1158, 135);
	glVertex2f(1172, 135);
	glVertex2f(1170, 190);
	glVertex2f(1160, 190);
	glEnd();

	// Shirt
	glBegin(GL_POLYGON);
	glColor3ub(shirt_r, shirt_g, shirt_b);
	glVertex2f(1155, 190);
	glVertex2f(1170, 190);
	glVertex2f(1170, 260);
	glVertex2f(1160, 260);
	glEnd();

	// Bag
	glBegin(GL_POLYGON);
	glColor3ub(156, 86, 47);
	glVertex2f(1170, 250);
	glVertex2f(1180, 245);
	glVertex2f(1185, 200);
	glVertex2f(1170, 195);
	glEnd();

	// Head
	drawCircle(1164, 273,
		232, 190, 123,
		1, 1.4,
		12);

	// Hair
	drawSemiCircle(1167, 277,
		1, 1,
		0, 0, 0,
		14,
		-80, 180);

	// Nose
	glBegin(GL_TRIANGLES);
	glColor3ub(232, 190, 123);
	glVertex2f(1155, 270);
	glVertex2f(1152, 260);
	glVertex2f(1157, 262);
	glEnd();

	// Eye
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3ub(0, 0, 0);
	glVertex2f(1156, 270);
	glEnd();
	glPointSize(1);

	// Lips
	glPointSize(1);
	glBegin(GL_POINTS);
	glColor3ub(0, 0, 0);
	glVertex2f(1158, 256);
	glVertex2f(1159, 257);
	glVertex2f(1160, 258);
	glEnd();
	glPointSize(1);

	glPopMatrix();
}

void highSchool() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	HS_drawBackground();
	HS_drawSun();
	HS_drawRoad();

	HS_drawHome();
	HS_drawSchool();
	HS_drawTuition();

	HS_drawLights();
	HS_drawStars();

	drawSchoolBoy(schoolboy_x, schoolboy_y,
		.5, .5,
		255, 0, 0);

	print("Bound by the endless cycle of home, school, tuition, each day slips away in a blur before we even catch our breath.",
		1, 1, 1, hs_subtitle_1_appear, 50, 30, .11, .11, 1);
}

// Pre University College Title Screen
void PUCTitleScreen() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Story Title
	print("CHAPTER 4",
		1, 1, 1, puc_chap_fade, 300, 500 - trans_x_chap4, .2, .2, 2);
	print("Senior Secondary School",
		1, 1, 1, puc_title_fade, 400 - trans_x_title4, 450 - trans_x_title4, .3, .3, 2);
}

void PUC_drawFloor() {
	// Floor
	glBegin(GL_POLYGON);
	glColor3ub(220, 200, 180);
	glVertex2f(0, 75);
	glVertex2f(1400, 75);
	glColor3ub(180, 160, 135);
	glVertex2f(775, 200);
	glVertex2f(625, 200);
	glEnd();

	// Floor Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(44, 76, 122);
	glVertex2f(0, 75);
	glVertex2f(1400, 75);
	glVertex2f(775, 200);
	glVertex2f(625, 200);
	glEnd();
}


void PUC_drawCenterWall() {
	// Center Wall
	glBegin(GL_POLYGON);
	glColor3ub(220, 200, 180);
	glVertex2f(625, 200);
	glVertex2f(775, 200);
	glVertex2f(775, 450);
	glVertex2f(625, 450);
	glEnd();

	// Center Wall Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(625, 200);
	glVertex2f(775, 200);
	glVertex2f(775, 450);
	glVertex2f(625, 450);
	glEnd();

	// Center Wall Strip
	glBegin(GL_POLYGON);
	glColor3ub(0, 130, 255);
	glVertex2f(625, 200);
	glVertex2f(775, 200);
	glVertex2f(775, 207.81);
	glVertex2f(625, 207.81);
	glEnd();

	// Center Wall Strip Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(625, 200);
	glVertex2f(775, 200);
	glVertex2f(775, 207.81);
	glVertex2f(625, 207.81);
	glEnd();
}


void PUC_drawCeiling() {
	// Ceiling
	glBegin(GL_POLYGON);
	glColor3ub(220, 200, 180);
	glVertex2f(625, 450);
	glVertex2f(775, 450);
	glColor3ub(240, 240, 240);
	glVertex2f(1400, 800);
	glVertex2f(0, 800);
	glEnd();

	// Ceiling Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(210, 200, 190);
	glVertex2f(625, 450);
	glVertex2f(775, 450);
	glVertex2f(1400, 800);
	glVertex2f(0, 800);
	glEnd();

}
void PUC_drawLeftWall() {
	// Left Wall
	glBegin(GL_POLYGON);
	glColor3ub(220, 200, 180);
	glVertex2f(0, 75);
	glVertex2f(625, 200);
	glVertex2f(625, 450);
	glVertex2f(0, 800);
	glEnd();

	// Left Wall Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(0, 75);
	glVertex2f(625, 200);
	glVertex2f(625, 450);
	glVertex2f(0, 800);
	glEnd();

	// Left Wall Bottom Strip
	glBegin(GL_POLYGON);
	glColor3ub(0, 130, 255);
	glVertex2f(0, 75);
	glVertex2f(625, 200);
	glVertex2f(625, 207.81);
	glVertex2f(0, 100);
	glEnd();

	// Left Wall Bottom Strip Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(0, 75);
	glVertex2f(625, 200);
	glVertex2f(625, 207.81);
	glVertex2f(0, 100);
	glEnd();
}

void PUC_drawRightWall() {
	// Right Wall
	glBegin(GL_POLYGON);
	glColor3ub(220, 200, 180);
	glVertex2f(775, 200);
	glVertex2f(1400, 75);
	glVertex2f(1400, 800);
	glVertex2f(775, 450);
	glEnd();

	// Right Wall Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(775, 200);
	glVertex2f(1400, 75);
	glVertex2f(1400, 800);
	glVertex2f(775, 450);
	glEnd();

	// Right Wall Bottom Strip
	glBegin(GL_POLYGON);
	glColor3ub(0, 130, 255);
	glVertex2f(1400, 75);
	glVertex2f(1400, 100);
	glVertex2f(775, 207.81);
	glVertex2f(775, 200);
	glEnd();

	// Right Wall Bottom Strip Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(1400, 75);
	glVertex2f(1400, 100);
	glVertex2f(775, 207.81);
	glVertex2f(775, 200);
	glEnd();
}



void PUC_drawLeftDoors() {
	// First Door
	glBegin(GL_POLYGON);
	glColor3ub(210, 210, 210);
	glVertex2f(150, 104);
	glVertex2f(350, 144);
	glVertex2f(350, 481);
	glVertex2f(150, 548);
	glEnd();

	// First Door Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(150, 104);
	glVertex2f(350, 144);
	glVertex2f(350, 481);
	glVertex2f(150, 548);
	glEnd();

	// First Wooden Door
	glBegin(GL_POLYGON);
	glColor3ub(63, 36, 19);
	glVertex2f(150, 104);
	glVertex2f(335, 158);
	glVertex2f(335, 472);
	glVertex2f(150, 548);
	glEnd();

	// First Wooden Door Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(150, 104);
	glVertex2f(335, 158);
	glVertex2f(335, 472);
	glVertex2f(150, 548);
	glEnd();

	// PCMB
	glBegin(GL_POLYGON);
	glColor3ub(255, 255, 255);
	glVertex2f(140, 520);
	glVertex2f(140, 490);
	glVertex2f(250, 490);
	glVertex2f(250, 520);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(140, 520);
	glVertex2f(140, 490);
	glVertex2f(250, 490);
	glVertex2f(250, 520);
	glEnd();

	drawCircle(138, 510, 100, 100, 100, 1, 1, 3);
	drawCircle(142, 510, 100, 100, 100, 1, 1, 3);

	drawCircle(138, 499, 100, 100, 100, 1, 1, 3);
	drawCircle(142, 499, 100, 100, 100, 1, 1, 3);

	print("Medical",
		0, 0, 0, 1, 160, 500, .1, .1, 2);

	// Door Knob
	drawCircle(320, 300,
		223, 189, 31, // Goldish Yellow
		1, 1,
		5);

	// Second Door
	glBegin(GL_POLYGON);
	glColor3ub(210, 210, 210);
	glVertex2f(450, 164);
	glVertex2f(550, 184);
	glVertex2f(550, 413);
	glVertex2f(450, 447);
	glEnd();

	// Second Door Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(450, 164);
	glVertex2f(550, 184);
	glVertex2f(550, 413);
	glVertex2f(450, 447);
	glEnd();

	// Second Wooden Door
	glBegin(GL_POLYGON);
	glColor3ub(63, 36, 19);
	glVertex2f(450, 164);
	glVertex2f(540, 194);
	glVertex2f(540, 403);
	glVertex2f(450, 447);
	glEnd();

	// Second Wooden Door Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(450, 164);
	glVertex2f(540, 194);
	glVertex2f(540, 403);
	glVertex2f(450, 447);
	glEnd();

	// CEBA
	glPushMatrix();

	glTranslatef(325, 10, 0);
	glScalef(.8, .8, 1);

	glBegin(GL_POLYGON);
	glColor3ub(255, 255, 255);
	glVertex2f(140, 520);
	glVertex2f(140, 490);
	glVertex2f(250, 490);
	glVertex2f(250, 520);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(140, 520);
	glVertex2f(140, 490);
	glVertex2f(250, 490);
	glVertex2f(250, 520);
	glEnd();

	drawCircle(138, 510, 100, 100, 100, 1, 1, 3);
	drawCircle(142, 510, 100, 100, 100, 1, 1, 3);

	drawCircle(138, 499, 100, 100, 100, 1, 1, 3);
	drawCircle(142, 499, 100, 100, 100, 1, 1, 3);

	print("Commerce",
		0, 0, 0, 1, 160, 500, .1, .1, 2);

	glPopMatrix();

	// Door Knob
	drawCircle(530, 300,
		223, 189, 31, // Goldish Yellow
		1, 1,
		3);
}


void PUC_drawRightDoors() {
	// First Door
	glBegin(GL_POLYGON);
	glColor3ub(210, 210, 210);
	glVertex2f(1049, 144);
	glVertex2f(1250, 104);
	glVertex2f(1250, 548);
	glVertex2f(1049, 481);
	glEnd();

	// First Door Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(1049, 144);
	glVertex2f(1250, 104);
	glVertex2f(1250, 548);
	glVertex2f(1049, 481);
	glEnd();

	// First Wooden Door
	glBegin(GL_POLYGON);
	glColor3ub(63, 36, 19);
	glVertex2f(1250, 104);
	glVertex2f(1065, 158);
	glVertex2f(1065, 472);
	glVertex2f(1250, 548);
	glEnd();

	// First Wooden Door Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(1250, 104);
	glVertex2f(1065, 158);
	glVertex2f(1065, 472);
	glVertex2f(1250, 548);
	glEnd();

	// PCMC
	glBegin(GL_POLYGON);
	glColor3ub(255, 255, 255);
	glVertex2f(1260, 520);
	glVertex2f(1260, 490);
	glVertex2f(1150, 490);
	glVertex2f(1150, 520);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(1260, 520);
	glVertex2f(1260, 490);
	glVertex2f(1150, 490);
	glVertex2f(1150, 520);
	glEnd();

	drawCircle(1258, 510, 100, 100, 100, 1, 1, 3);
	drawCircle(1262, 510, 100, 100, 100, 1, 1, 3);

	drawCircle(1258, 499, 100, 100, 100, 1, 1, 3);
	drawCircle(1262, 499, 100, 100, 100, 1, 1, 3);

	print("Non-Med.",
		0, 0, 0, 1, 1165, 500, .1, .1, 2);

	// Door Knob
	drawCircle(1080, 300,
		223, 189, 31, // Goldish Yellow
		1, 1,
		5);

	// Second Door
	glBegin(GL_POLYGON);
	glColor3ub(210, 210, 210);
	glVertex2f(850, 184);
	glVertex2f(950, 164);
	glVertex2f(950, 447);
	glVertex2f(850, 413);
	glEnd();

	// Second Door Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(850, 184);
	glVertex2f(950, 164);
	glVertex2f(950, 447);
	glVertex2f(850, 413);
	glEnd();

	// Second Wooden Door
	glBegin(GL_POLYGON);
	glColor3ub(63, 36, 19);
	glVertex2f(950, 164);
	glVertex2f(860, 194);
	glVertex2f(860, 403);
	glVertex2f(950, 447);
	glEnd();

	// Second Wooden Door Border
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(950, 164);
	glVertex2f(860, 194);
	glVertex2f(860, 403);
	glVertex2f(950, 447);
	glEnd();


	// PCME
	glPushMatrix();

	glTranslatef(-45, 10, 0);
	glScalef(.8, .8, 1);

	glBegin(GL_POLYGON);
	glColor3ub(255, 255, 255);
	glVertex2f(1260, 520);
	glVertex2f(1260, 490);
	glVertex2f(1150, 490);
	glVertex2f(1150, 520);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	glVertex2f(1260, 520);
	glVertex2f(1260, 490);
	glVertex2f(1150, 490);
	glVertex2f(1150, 520);
	glEnd();

	drawCircle(1258, 510, 100, 100, 100, 1, 1, 3);
	drawCircle(1262, 510, 100, 100, 100, 1, 1, 3);

	drawCircle(1258, 499, 100, 100, 100, 1, 1, 3);
	drawCircle(1262, 499, 100, 100, 100, 1, 1, 3);

	print("Arts",
		0, 0, 0, 1, 1165, 500, .1, .1, 2);

	glPopMatrix();

	// Door Knob
	drawCircle(870, 300,
		223, 189, 31, // Goldish Yellow
		1, 1,
		3);
}


void PUC_drawBoard() {
	// Board Hanging Line
	glLineWidth(4);
	glBegin(GL_LINES);
	glColor3ub(20, 20, 20);
	glVertex2f(550, 800);
	glVertex2f(550, 750);
	glVertex2f(850, 800);
	glVertex2f(850, 750);
	glEnd();
	glLineWidth(1);

	// Board Border
	glBegin(GL_POLYGON);
	glColor3ub(20, 20, 20);
	glVertex2f(450, 750);
	glVertex2f(450, 600);
	glVertex2f(950, 600);
	glVertex2f(950, 750);
	glEnd();

	// Board
	glBegin(GL_POLYGON);
	glColor3ub(0, 131, 255);
	glVertex2f(452, 748);
	glColor3ub(0, 104, 204);
	glVertex2f(452, 602);
	glVertex2f(948, 602);
	glColor3ub(0, 131, 255);
	glVertex2f(948, 748);
	glEnd();



	print("Dasmesh Public School",
		1, 1, 1, 1, 530, 660, .15, .15, 2);

	print("Faridkot",
		1, 1, 1, 1, 650, 630, .12, .12, 1);
}
void drawWallClock(GLfloat x, GLfloat y, GLfloat radius) {
	// Clock face
	drawCircle(x, y, 255, 255, 255, 1, 1, radius);

	// Clock outline
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	glColor3ub(20, 20, 20);
	for (int i = 0; i < 360; i += 5)
		glVertex2f(x + radius * sin(i * PI / 180), y + radius * cos(i * PI / 180));
	glEnd();
	glLineWidth(1);

	// 12, 3, 6, 9 hour marks (optional)
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3ub(20, 20, 20);
	// 12
	glVertex2f(x, y + radius * 0.8);
	glVertex2f(x, y + radius);
	// 3
	glVertex2f(x + radius * 0.8, y);
	glVertex2f(x + radius, y);
	// 6
	glVertex2f(x, y - radius * 0.8);
	glVertex2f(x, y - radius);
	// 9
	glVertex2f(x - radius * 0.8, y);
	glVertex2f(x - radius, y);
	glEnd();
	glLineWidth(1);

	// Hour and minute hands (fixed time, e.g., 10:10)
	glLineWidth(4);
	glBegin(GL_LINES);
	glColor3ub(20, 20, 20);
	// Hour hand
	glVertex2f(x, y);
	glVertex2f(x + radius * 0.4 * sin(300 * PI / 180), y + radius * 0.4 * cos(300 * PI / 180)); // 10 o'clock
	// Minute hand
	glVertex2f(x, y);
	glVertex2f(x + radius * 0.7 * sin(60 * PI / 180), y + radius * 0.7 * cos(60 * PI / 180)); // 2 o'clock
	glEnd();
	glLineWidth(1);

	// Center dot
	drawCircle(x, y, 20, 20, 20, 1, 1, 5);
}

// Pre University College
void PUC() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	PUC_drawFloor();
	PUC_drawCenterWall();
	PUC_drawCeiling();
	drawWallClock(700, 370, 30);
	PUC_drawLeftWall();
	PUC_drawRightWall();

	PUC_drawLeftDoors();
	PUC_drawRightDoors();
	PUC_drawBoard();

	// Red Boy
	drawSchoolBoy(trans_x_sb1, trans_y_sb1,
		1.4, 1.4,
		255, 0, 0);

	// Green Boy
	drawSchoolBoy(trans_x_sb2, trans_y_sb2,
		-1.4, 1.4,
		0, 255, 0);

	print("Some students choose PCMB, some choose PCMC, and some...",
		1, 1, 1, puc_subtitle_1_fade, 300, 30, .14, .14, 1);
}

// Engineering College Title Screen
void engineeringCollegeTitleScreen() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Story Title
	print("CHAPTER 5",
		1, 1, 1, eng_chap_fade, 300 + trans_x_chap5, 400, .2, .2, 2);
	print("Engineering College",
		1, 1, 1, eng_title_fade, 400 - trans_x_title5, 350, .3, .3, 2);
}

void drawGraduatedBoy(GLfloat tx, GLfloat ty,
	GLfloat sx, GLfloat sy,
	GLfloat shirt_r, GLfloat shirt_g, GLfloat shirt_b) {
	glPushMatrix();

	glScalef(sx, sy, 0);
	glTranslatef(tx, ty, 0);

	// Shoes
	drawSemiCircle(1160, 120,
		1, 1,
		255, 255, 255,
		10,
		-90, 91);

	// Shoe Extension
	glBegin(GL_POLYGON);
	glColor3ub(255, 255, 255);
	glVertex2f(1160, 120);
	glVertex2f(1170, 120);
	glVertex2f(1170, 135);
	glVertex2f(1160, 135);
	glEnd();

	// Pants
	glBegin(GL_POLYGON);
	glColor3ub(0, 0, 200);
	glVertex2f(1158, 135);
	glVertex2f(1172, 135);
	glVertex2f(1170, 190);
	glVertex2f(1160, 190);
	glEnd();

	// Shirt
	glBegin(GL_POLYGON);
	glColor3ub(shirt_r, shirt_g, shirt_b);
	glVertex2f(1155, 190);
	glVertex2f(1170, 190);
	glVertex2f(1170, 260);
	glVertex2f(1160, 260);
	glEnd();

	// Bag
	glBegin(GL_POLYGON);
	glColor3ub(156, 86, 47);
	glVertex2f(1170, 250);
	glVertex2f(1180, 245);
	glVertex2f(1185, 200);
	glVertex2f(1170, 195);
	glEnd();

	// Head
	drawCircle(1164, 273,
		232, 190, 123,
		1, 1.4,
		12);

	// Hair
	drawSemiCircle(1167, 277,
		1, 1,
		0, 0, 0,
		14,
		-80, 180);

	// Graduation Cap
	glBegin(GL_POLYGON);
	glColor3ub(50, 50, 50); // Barely Black
	glVertex2f(1144, 282);
	glVertex2f(1190, 268);
	glVertex2f(1189, 285);
	glVertex2f(1165, 297);
	glEnd();

	// Graduation Cap Thread
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	glColor3ub(240, 240, 40);
	glVertex2f(1173, 281);
	glVertex2f(1186, 272);
	glVertex2f(1190, 258);
	glEnd();
	glLineWidth(1);
	drawCircle(1190, 258,
		240, 240, 40,
		1, 1.2,
		3);

	// Nose
	glBegin(GL_TRIANGLES);
	glColor3ub(232, 190, 123);
	glVertex2f(1155, 270);
	glVertex2f(1152, 260);
	glVertex2f(1157, 262);
	glEnd();

	// Eye
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3ub(0, 0, 0);
	glVertex2f(1156, 270);
	glEnd();
	glPointSize(1);

	// Lips
	glPointSize(1);
	glBegin(GL_POINTS);
	glColor3ub(0, 0, 0);
	glVertex2f(1158, 256);
	glVertex2f(1159, 257);
	glVertex2f(1160, 258);
	glEnd();
	glPointSize(1);

	glPopMatrix();
}

void EC_drawBackground() {
	// Background
	glBegin(GL_POLYGON);
	glColor3ub(12, 172, 232); // Sky Blue
	glVertex2f(0, 800);
	glVertex2f(1400, 800);
	glVertex2f(1400, 400);
	glVertex2f(0, 400);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3ub(12, 172, 232); // Sky Blue
	glVertex2f(0, 400);
	glVertex2f(1400, 400);
	glColor3ub(82, 163, 42); // Green Grass
	glVertex2f(1400, 125);
	glVertex2f(0, 125);
	glEnd();
}

void EC_drawRoad() {
	glBegin(GL_POLYGON);
	glColor3ub(40, 40, 40);
	glVertex2f(0, 75);
	glVertex2f(1400, 75);
	glVertex2f(1400, 125);
	glVertex2f(0, 125);
	glEnd();

	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3ub(255, 255, 255);
	glVertex2f(0, 100);
	glVertex2f(100, 100);

	glVertex2f(120, 100);
	glVertex2f(220, 100);

	glVertex2f(240, 100);
	glVertex2f(340, 100);

	glVertex2f(360, 100);
	glVertex2f(460, 100);

	glVertex2f(480, 100);
	glVertex2f(580, 100);

	glVertex2f(600, 100);
	glVertex2f(700, 100);

	glVertex2f(720, 100);
	glVertex2f(820, 100);

	glVertex2f(840, 100);
	glVertex2f(940, 100);

	glVertex2f(960, 100);
	glVertex2f(1060, 100);

	glVertex2f(1080, 100);
	glVertex2f(1180, 100);

	glVertex2f(1200, 100);
	glVertex2f(1300, 100);

	glVertex2f(1320, 100);
	glVertex2f(1420, 100);

	glEnd();
	glLineWidth(1);
}




void EC_drawFrontFacingBuilding() {
	// Front Facing Building
	glBegin(GL_POLYGON);
	glColor3ub(203, 109, 81);
	glVertex2f(550, 125);
	glColor3ub(203, 109, 81);
	glVertex2f(850, 125);
	glColor3ub(203, 109, 81);
	glVertex2f(850, 650);
	glColor3ub(203, 109, 81);
	glVertex2f(550, 650);
	glEnd();

	// Front Facing Building Mesh
	glBegin(GL_LINES);
	glColor3ub(29, 2, 0);

	// Vertical Lines - 4
	glVertex2f(550, 650);
	glVertex2f(550, 125);

	glVertex2f(625, 650);
	glVertex2f(625, 125);

	glVertex2f(700, 650);
	glVertex2f(700, 125);

	glVertex2f(775, 650);
	glVertex2f(775, 125);

	glVertex2f(850, 650);
	glVertex2f(850, 125);

	// Horizontal Lines - 10
	glVertex2f(550, 125);
	glVertex2f(850, 125);

	glVertex2f(550, 177.5);
	glVertex2f(850, 177.5);

	glVertex2f(550, 230);
	glVertex2f(850, 230);

	glVertex2f(550, 282.5);
	glVertex2f(850, 282.5);

	glVertex2f(550, 335);
	glVertex2f(850, 335);

	glVertex2f(550, 387.5);
	glVertex2f(850, 387.5);

	glVertex2f(550, 440);
	glVertex2f(850, 440);

	glVertex2f(550, 492.5);
	glVertex2f(850, 492.5);

	glVertex2f(550, 545);
	glVertex2f(850, 545);

	glVertex2f(550, 598);
	glVertex2f(850, 598);

	glVertex2f(550, 650);
	glVertex2f(850, 650);
	glEnd();

	// Door
	glBegin(GL_POLYGON);
	glColor3ub(133, 65, 43);
	glVertex2f(626, 125);
	glColor3ub(133, 65, 43);
	glVertex2f(774, 125);
	glColor3ub(133, 65, 43);
	glVertex2f(774, 282);
	glColor3ub(133, 65, 43);
	glVertex2f(626, 282);
	glEnd();

	glBegin(GL_LINES);
	glColor3ub(133, 65, 43);
	glVertex2f(700, 282);
	glVertex2f(700, 125);
	glEnd();

	drawCircle(690, 206, 29, 2, 0, 1, 1, 3);
	drawCircle(690, 202, 29, 2, 0, 1, 1, 3);
	drawCircle(690, 198, 29, 2, 0, 1, 1, 3);

	drawCircle(710, 206, 29, 2, 0, 1, 1, 3);
	drawCircle(710, 202, 29, 2, 0, 1, 1, 3);
	drawCircle(710, 198, 29, 2, 0, 1, 1, 3);
}



void EC_drawLeftWing() {
	// Left Wing
	glBegin(GL_POLYGON);
	glColor3ub(133, 65, 43);
	glVertex2f(500, 125);
	glVertex2f(550, 125);
	glVertex2f(550, 598);
	glVertex2f(500, 598);
	glEnd();

	// Left Building
	glBegin(GL_POLYGON);
	glColor3ub(203, 109, 81);
	glVertex2f(200, 184);
	glColor3ub(203, 109, 81);
	glVertex2f(500, 125);
	glColor3ub(203, 109, 81);
	glVertex2f(500, 598);
	glColor3ub(203, 109, 81);
	glVertex2f(200, 539);
	glEnd();

	// Left Building
	glBegin(GL_LINE_LOOP);
	glColor3ub(133, 65, 43);
	glVertex2f(200, 184);
	glVertex2f(500, 125);
	glVertex2f(500, 598);
	glVertex2f(200, 539);
	glEnd();

	// Windows Edges
	glBegin(GL_LINES);
	glColor3ub(29, 2, 0);
	glVertex2f(500, 125);
	glVertex2f(500, 598);

	glVertex2f(400, 144);
	glVertex2f(400, 576);

	glVertex2f(300, 164);
	glVertex2f(300, 556);

	glVertex2f(200, 184);
	glVertex2f(200, 539);
	glEnd();
}

void EC_drawRightWing() {
	// Right Wing
	glBegin(GL_POLYGON);
	glColor3ub(133, 65, 43);
	glVertex2f(850, 125);
	glVertex2f(900, 125);
	glVertex2f(900, 598);
	glVertex2f(850, 598);
	glEnd();

	// Right Building
	glBegin(GL_POLYGON);
	glColor3ub(203, 109, 81);
	glVertex2f(900, 125);
	glColor3ub(203, 109, 81);
	glVertex2f(1200, 184);
	glColor3ub(203, 109, 81);
	glVertex2f(1200, 539);
	glColor3ub(203, 109, 81);
	glVertex2f(900, 598);
	glEnd();

	// Right Building
	glBegin(GL_LINE_LOOP);
	glColor3ub(133, 65, 43);
	glVertex2f(900, 125);
	glVertex2f(1200, 184);
	glVertex2f(1200, 539);
	glVertex2f(900, 598);
	glEnd();

	// Windows Edges
	glBegin(GL_LINES);
	glColor3ub(29, 2, 0);
	glVertex2f(900, 125);
	glVertex2f(900, 598);

	glVertex2f(1000, 144);
	glVertex2f(1000, 576);

	glVertex2f(1100, 164);
	glVertex2f(1100, 556);

	glVertex2f(1200, 184);
	glVertex2f(1200, 539);
	glEnd();
}

void EC_drawTrees() {
	// Left Trees
	drawTree(430, 130, .5, .5);
	drawTree(360, 140, .48, .48);
	drawTree(290, 150, .46, .46);
	drawTree(220, 160, .44, .44);

	// Right Trees
	drawTree(940, 130, .5, .5);
	drawTree(1010, 140, .48, .48);
	drawTree(1080, 150, .46, .46);
	drawTree(1150, 160, .44, .44);
}

void EC_drawBoys() {
	// Red Boy
	drawSchoolBoy(trans_x_ec_sb1, trans_y_ec_sb,
		.75, .75,
		255, 0, 0);

	// Green Boy
	drawSchoolBoy(trans_x_ec_sb2, trans_y_ec_sb,
		-.75, .75,
		0, 255, 0);

	// Red Graduate
	drawGraduatedBoy(trans_x_ec_gb, trans_y_ec_gb,
		.75, .75,
		255, 0, 0);

	// Green Graduate
	drawGraduatedBoy(trans_x_ec_gb - 110, trans_y_ec_gb,
		.75, .75,
		0, 255, 0);
}

void EC_drawEngineeringCollege() {
	EC_drawFrontFacingBuilding();
	EC_drawLeftWing();
	EC_drawRightWing();
}




void EC_drawBoard() {
	glBegin(GL_POLYGON);
	glColor3ub(1, 1, 1);
	glVertex2f(400, 660);
	glVertex2f(1000, 660);
	glVertex2f(1000, 760);
	glVertex2f(400, 760);
	glEnd();

	glLineWidth(10);
	glBegin(GL_LINES);
	glVertex2f(525, 650);
	glVertex2f(525, 670);
	glEnd();
	glLineWidth(1);

	glLineWidth(10);
	glBegin(GL_LINES);
	glVertex2f(675, 650);
	glVertex2f(675, 670);
	glEnd();
	glLineWidth(1);

	glBegin(GL_POLYGON);
	glColor3ub(220, 69, 19);
	glVertex2f(405, 665);
	glVertex2f(995, 665);
	glColor3ub(204, 59, 14);
	glVertex2f(995, 755);
	glVertex2f(405, 755);
	glEnd();

	print("Thapar Institute of Engineering & Technology",
		1, 1, 1, 1,
		480, 710,
		.1, .1,
		1);

	print("PATIALA",
		1, 1, 1, 1,
		650, 690,
		.08, .08,
		1);
}

// Engineering College
void engineeringCollege() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	EC_drawBackground();
	EC_drawRoad();

	EC_drawEngineeringCollege();

	EC_drawTrees();
	EC_drawBoys();

	EC_drawBoard();

	print("Some students end up in Engineering, irrespective of what path they took in the past...",
		1, 1, 1, ec_subtitle_1_fade, 60, 30, .14, .14, 1);
}


// Function to Render Scene
void renderScene() {
	// Switch to know which scene is playing
	switch (SCENE_ID) {
	case 0:
		introduction();
		break;
	case 1:
		summary();
		break;
	case 2:
		kindergartenTitleScreen();
		break;
	case 3:
		kindergarten();
		break;
	case 4:
		primarySchoolTitleScreen();
		break;
	case 5:
		primarySchool();
		break;
	case 6:
		highSchoolTitleScreen();
		break;
	case 7:
		highSchool();
		break;
	case 8:
		PUCTitleScreen();
		break;
	case 9:
		PUC();
		break;
	case 10:
		engineeringCollegeTitleScreen();
		break;
	case 11:
		engineeringCollege();
		break;
	
	default:
		break;
	}

	// glFush sends it to the Display Buffer
	glFlush();
}

// Function to Handle Mouse Clicks
void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		std::cout << x << "\t" << 800 - y << "\n";
}

// Animator Updation Function
void update(int) {
	// Introduction
	if (SCENE_ID == 0) {
		if (title_fade < 1)
			title_fade += .003;
		else
			intro_next_text_appear = 1;
	}

	// Summary
	if (SCENE_ID == 1) {
		// Fade in the single opening line...
		if (summary_intro_fade < 1.0) {
			summary_intro_fade += 0.02;
			if (summary_intro_fade > 1.0)
				summary_intro_fade = 1.0;      // clamp at 1
		}
		else {
			// Once fully faded in, show the �Press N� prompt
			summary_next_text_appear = 1;
		}
	}

	// Kindergarten Title Screen
	if (SCENE_ID == 2) {
		if (trans_x_chap1 < 100)
			trans_x_chap1 += 1;

		if (trans_x_title1 < 100)
			trans_x_title1 += 1;

		if (kg_chap_fade < 1)
			kg_chap_fade += .025;

		if (kg_title_fade < 1)
			kg_title_fade += .025;
	}

	// Kindergarten
	if (SCENE_ID == 3) {
		if (kg_a_fade < 1)
			kg_a_fade += .025;
		else
			if (kg_apple_fade < 1)
				kg_apple_fade += .025;
			else
				if (kg_b_fade < 1)
					kg_b_fade += .025;
				else
					if (kg_ball_fade < 1)
						kg_ball_fade += .025;
					else
						if (kg_soon_fade < 1)
							kg_soon_fade += .025;
						else
							kg_subtitle_1_appear = 1;

	}

	// Primary School Title Screen
	if (SCENE_ID == 4) {
		if (trans_x_chap2 < 100)
			trans_x_chap2 += 1;

		if (trans_y_title2 < 100)
			trans_y_title2 += 1;

		if (ps_chap_fade < 1)
			ps_chap_fade += .01;

		if (ps_title_fade < 1)
			ps_title_fade += .01;
	}

	// Primary School
	if (SCENE_ID == 5) {
		if (trans_x_kid1 < 40)
			trans_x_kid1 += .4;


		if (trans_x_kid3 < 40)
			trans_x_kid3 += .3;

		if (trans_x_ball < 50)
			trans_x_ball += .4;

		if (ps_subtitle_1_appear < 1)
			ps_subtitle_1_appear += .005;
		else {
			if (ps_subtitle_2_appear < 1) {
				trans_subtitle_1_done = 200;
				ps_subtitle_2_appear += .005;
			}
		}
	}

	// High School Title Screen
	if (SCENE_ID == 6) {
		if (trans_x_chap3 < 100)
			trans_x_chap3 += 1;

		if (trans_x_title3 < 100)
			trans_x_title3 += 1;

		if (hs_chap_fade < 1)
			hs_chap_fade += .01;

		if (hs_title_fade < 1)
			hs_title_fade += .01;
	}

	// High School
	if (SCENE_ID == 7) {
		if (!chapter_1_done) {
			delay(1);
			schoolboy_y -= 5000;
			chapter_1_done = true;
		}

		if (chapter_1_done && !chapter_2_done) {
			if (schoolboy_x >= 300) {
				schoolboy_x -= 5;
			}
			else {
				schoolboy_y += 5000;
				chapter_2_done = true;
			}
		}

		if (chapter_1_done && chapter_2_done && !chapter_3_done && !sun_has_set) {
			if (sun_r <= 255)
				sun_r += .25;
			if (sun_g <= 255)
				sun_g += .25;
			if (sun_b <= 255)
				sun_b += .25;

			if (star_alpha <= 200)
				star_alpha += 1;

			if (grass_r <= 255)
				grass_r += .25;
			if (grass_g <= 220)
				grass_g += .25;
			if (grass_b >= 65)
				grass_b += .25;

			if (window_top_r <= 255)
				window_top_r += .25;
			if (window_top_g <= 220)
				window_top_g += .25;
			if (window_top_b >= 65)
				window_top_b -= .25;

			if (window_bottom_r <= 255)
				window_bottom_r += .25;
			if (window_bottom_g <= 220)
				window_bottom_g += .25;
			if (window_bottom_b >= 65)
				window_bottom_b -= .25;

			if (sky_r <= 0)
				sky_r += .25;
			if (sky_g >= 0)
				sky_g -= .25;
			if (sky_b >= 0)
				sky_b -= .25;

			if (sun_move_left < 1100)
				sun_move_left += 1.5;
			else
				sun_has_set = true;

			if (sun_move_left > 500)
				sun_moved_half = true;
		}

		if (sun_moved_half && !chapter_4_done) {
			if (schoolboy_y != 220)
				schoolboy_y -= 5000;

			if (schoolboy_x >= -1000)
				schoolboy_x -= 5;
			else {
				schoolboy_y += 5000;
				chapter_4_done = true;
			}
		}

		if (chapter_4_done) {
			if (schoolboy_y != 5220 && !tuition_done) {
				schoolboy_y += 5000;
				tuition_done = true;
			}
		}

		if (sun_has_set) {
			if (schoolboy_y != 220)
				schoolboy_y -= 5000;
			chapter_5_done = true;
		}

		if (chapter_5_done) {
			if (schoolboy_x <= 1150)
				schoolboy_x += 5;
			else {
				if (schoolboy_y != 5220)
					schoolboy_y += 5000;
			}

			if (hs_subtitle_1_appear < 1) {
				hs_subtitle_1_appear += .005;
			}
		}
	}

	// Pre University College Title Screen
	if (SCENE_ID == 8) {
		if (trans_x_chap4 < 100)
			trans_x_chap4 += 1;

		if (trans_x_title4 < 100)
			trans_x_title4 += 1;

		if (puc_chap_fade < 1)
			puc_chap_fade += .01;

		if (puc_title_fade < 1)
			puc_title_fade += .01;
	}

	// Pre University College
	if (SCENE_ID == 9) {
		if (puc_subtitle_1_fade < 1)
			puc_subtitle_1_fade += 0.005;

		if (!puc_begin_anim) {
			delay(1);
			puc_begin_anim = true;
		}

		if (!puc_end_anim) {
			if (trans_x_sb1 >= -930)
				trans_x_sb1 -= 1;
			if (trans_y_sb1 <= -20)
				trans_y_sb1 += .1;

			if (trans_x_sb2 >= -1930)
				trans_x_sb2 -= 1;
			if (trans_y_sb2 <= -20)
				trans_y_sb2 += .1;

			if (trans_y_sb1 >= -20 && trans_y_sb2 >= -20)
				puc_end_anim = true;
		}

		if (puc_end_anim) {
			delay(1);

			if (trans_y_sb1 <= 5000)
				trans_y_sb1 += 5000;

			if (trans_y_sb2 <= 5000)
				trans_y_sb2 += 5000;
		}
	}

	// Engineering College Title Screen
	if (SCENE_ID == 10) {
		if (trans_x_chap5 < 100)
			trans_x_chap5 += 1;

		if (trans_x_title5 < 100)
			trans_x_title5 += 1;

		if (eng_chap_fade < 1)
			eng_chap_fade += .025;

		if (eng_title_fade < 1)
			eng_title_fade += .025;
	}

	if (SCENE_ID == 11) {
		if (trans_x_ec_sb1 >= -180)
			trans_x_ec_sb1 -= 4;
		if (trans_x_ec_sb2 >= -2050)
			trans_x_ec_sb2 -= 4;

		if (trans_x_ec_sb1 <= -180 && trans_x_ec_sb2 <= -2050 && !ec_graduation_done) {
			trans_y_ec_sb += 1000;
			ec_graduation_done = true;
		}

		if (ec_graduation_done) {
			if (trans_y_ec_gb != 40) {
				trans_y_ec_gb -= 1000;
			}
			if (trans_x_ec_gb >= -1200)
				trans_x_ec_gb -= 2;
		}

		if (ec_subtitle_1_fade <= 1)
			ec_subtitle_1_fade += 0.005;
	}

	// Recalls the Display Function
	glutPostRedisplay();

	// Creates a Timer of 25ms
	glutTimerFunc(25, update, 0);
}

// Keyboard Action
void keyPress(unsigned char key, int x, int y) {
	switch (key) {
		// Go to Previous Scene
	case 'b':
	case 'B':
		if (SCENE_ID == 0)
			break;
		SCENE_ID--;
		break;
		// Go to Next Scene
	case 'n':
	case 'N':
		if (SCENE_ID == 15)
			break;
		SCENE_ID++;
		break;
		// Quit Story
	case 'q':
	case 'Q':
		exit(0);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

// Function to Initialize Screen
void initializeScreen() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1400, 0, 800);
}

// Main Function
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1400, 800);
	glutCreateWindow("From Bell to Bell: Student Sprint");

	// Enables Transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Enable Smoothening
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Display Function
	glutDisplayFunc(renderScene);

	// Input Functions
	glutKeyboardFunc(keyPress);
	glutMouseFunc(mouseClick);

	initializeScreen();

	// Timer Function
	// every 25 milliseconds, update function is called
	glutTimerFunc(25, update, 0);

	glutMainLoop();

	return 0;
}

