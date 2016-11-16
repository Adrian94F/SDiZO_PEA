#include "Header.h"
/*************************************************************************************/
MatrixGraph graph;										// graf
vector <unsigned char> path;							// �cie�ka
vector <vector <float>> vertices;						// wsp�rz�dne wierzcho�k�w
double alfa;											// k�t pomi�dzy wierzcho�kami
float Rmax = 7.0, Rmin = 5.0, Smin = 1e+30, Smax = 0;		// max i min promie�, max i min suma d�ugo�ci
vector <float> r;										// promienie
int n;													// liczba wierzcho�k�w
string name;											// nazwa pliku

/*************************************************************************************/
void Axes(void)
{
	float l = 4;
	glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
	glBegin(GL_LINES); // rysowanie osi x
	glVertex2f(-l, 0.0);
	glVertex2f(l, 0.0);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
	glBegin(GL_LINES);  // rysowanie osi y
	glVertex2f(0.0, -l);
	glVertex2f(0.0, l);
	glEnd();
}

/*************************************************************************************/
void Circle(float cx, float cy, float r, int num_segments)
{
	glColor3f(0.0f, 0.0f, 1.0f);		// Ustawienie aktualnego koloru rysowania na niebieski
	glBegin(GL_POLYGON);
	for (int i = 0; i < num_segments; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle

		float x = r * cos(theta);//calculate the x component
		float y = r * sin(theta);//calculate the y component

		glVertex2f(x + cx, y + cy);//output vertex
	}
	glEnd();
}

/*************************************************************************************/
void RenderString(float x, float y, void *font, int n, float3 color)
{
	string str = to_string(n);
	const unsigned char* foo = reinterpret_cast<const unsigned char*>(str.c_str());

	glColor3fv(color);
	glRasterPos2f(x, y);

	for (int i = 0; i < str.length(); i++)
		glutBitmapCharacter(font, foo[i]);
}

/*************************************************************************************/
void RenderString(float x, float y, void *font, string s, float3 color)
{
	glColor3fv(color);
	glRasterPos2f(x, y);
	for (int i = 0; i < s.length(); i++)
		glutBitmapCharacter(font, s[i]);
}

void Prepare(void)
{
	vertices.clear();
	r.clear();
	// wierzcho�ki na okr�gu oddalone o k�t alfa w odleg�o�ci od �rodka zale�nej od �redniej d�ugo�ci dr�g od nich
	alfa = 2 * 3.14159265359 / graph.GetSize();
	n = graph.GetSize();

	for (int i = 0; i < n; i++)
	{
		float sum = 0;
		for (int j = 0; j < n; j++)
		{
			float c = graph.GetNodes()[i][j];
			if (i != j)
				sum += c;
		}
		r.push_back(sum);
		Smax = sum > Smax ? sum : Smax;
		Smin = sum < Smin ? sum : Smin;
	}

	// ustalenie d�ugo�ci promieni
	for (int i = 0; i < n; i++)
	{
		r[i] = (r[i] - Smin) / (Smax - Smin) * (Rmax - Rmin) + Rmin;
	}

	// ustelenie wsp�rz�dnych wierzcho�k�w
	for (int i = 0; i < n; i++)
	{
		float _r = r[i];
		double _alfa = i * alfa;
		float px = _r * (float)cos(_alfa);
		float py = _r * (float)sin(_alfa);
		vertices.push_back(vector <float>());
		vertices[i].push_back(px);
		vertices[i].push_back(py);
	}
}

/*************************************************************************************/
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);			// Czyszczenie okna aktualnym kolorem czyszcz�cym

	//Axes();

	glColor3f(0.1f, 0.1f, 0.1f);			// Ustawienie aktualnego koloru rysowania na szary

	Prepare();								// przygotowanie warto�ci

	for (int i = 0; i < n - 1; i++)			// rysowanie linii
	{
		for (int j = i + 1; j < n; j++)
		{
			glBegin(GL_LINE_STRIP);
			glVertex2f(vertices[i][0], vertices[i][1]);
			glVertex2f(vertices[j][0], vertices[j][1]);
			glEnd();
		}
	}
	if (path.size() == graph.GetSize() + 1)								// rysowanie �cie�ki
	{
		glColor3f(1.0f, 1.0f, 1.0f);		// Ustawienie aktualnego koloru rysowania na bia�y
		for (int i = 0; i < n; i++)
		{
			glBegin(GL_LINE_STRIP);
			glVertex2f(vertices[path[i]][0], vertices[path[i]][1]);
			glVertex2f(vertices[path[i + 1]][0], vertices[path[i + 1]][1]);
			glEnd();
		}
	}

	for (int i = 0; i < n; i++)				// rysowanie wierzcho�k�w
	{
		Circle(vertices[i][0], vertices[i][1], 0.3, 20);
		float3 color = { 1.0f, 1.0f, 1.0f };
		string str = to_string(i + 1);
		float offset = str.length() * 0.045;
		RenderString(vertices[i][0] - offset, vertices[i][1] - 0.06, GLUT_BITMAP_HELVETICA_12, to_string(i + 1), color);
	}

	// rysowanie danych grafu:
	//   nazwa pliku
	//   optymalna �cie�ka
	//   koszt
	float3 color = { 1.0, 0.0, 0.0 };
	string description[4] = { "Nazwa pliku: " + name,"Rozmiar instancji: " + to_string(graph.GetSize()), "Sciezka: ", "Koszt: " };
	if (path.size() != graph.GetSize() + 1)
	{
		description[2] += "NIE ZNALEZIONO!";
		description[3] += "NIE ZNALEZIONO!";
	}
	else
	{
		for (int i = 0; i < path.size(); i++)
			description[2] += to_string(path[i] + 1) + " ";
		description[3] += to_string((int)KomiwojazerGetWeight(path, graph));
	}
	float offset = 0.3;
	for (int i = 0; i < 4; i++)
		RenderString(-7, 7 - (i*offset), GLUT_BITMAP_HELVETICA_12, description[i], color);

	glFlush();								// Przekazanie polece� rysuj�cych do wykonania
	glutSwapBuffers();
}

/*************************************************************************************/
void MyInit(void)
{
	// Kolor wn�trza okna
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

/*************************************************************************************/
void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	GLfloat AspectRatio;									// Deklaracja zmiennej AspectRatio  okre�laj�cej proporcj� wymiar�w okna
	if (vertical == 0)										// Zabezpieczenie przed dzieleniem przez 0
		vertical = 1;
	glViewport(0, 0, horizontal, vertical);					// Ustawienie wielko�ciokna okna widoku (viewport)
	glMatrixMode(GL_PROJECTION);							// Prze��czenie macierzy bie��cej na macierz projekcji
	glLoadIdentity();										// Czyszcznie macierzy bie��cej           
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;	// Wyznaczenie wsp�czynnika  proporcji okna
	if (horizontal <= vertical)
		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);
	else
		glOrtho(-7.5*AspectRatio, 7.5*AspectRatio, -7.5, 7.5, 10.0, -10.0);
	glMatrixMode(GL_MODELVIEW);								// Prze��czenie macierzy bie��cej na macierz widoku modelu                                    
	glLoadIdentity();										// Czyszcenie macierzy bie��cej
}

/*************************************************************************************/
//void keys(unsigned char key, int x, int y)
//{
//	if (key == 32) glutLeaveMainLoop(); // zamknij spacj�
//}

/*************************************************************************************/
void GLdisplay(int argc, char **argv, MatrixGraph g, vector <unsigned char> p, string n)
{
	if (n.length() == 0)
		return;
	//przypisanie zmiennych z funkcji do globalnych
	graph = g;
	path = p;
	name = n;
	glutInit(&argc, argv);
	// Ustawienie trybu wy�wietlania
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	// Rozmiar okna
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(800, 800);
	// Utworzenie okna i okre�lenie tre�ci napisu w nag��wku okna
	glutCreateWindow("Graf");

	// Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn� (callback)
	glutDisplayFunc(RenderScene);
	// Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn� za zmiany rozmiaru okna
	glutReshapeFunc(ChangeSize);
	// klawisze
	//glutKeyboardFunc(keys);
	// Inicjalizacja
	MyInit();
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	// Funkcja uruchamia szkielet biblioteki GLUT
	glutMainLoop();

}