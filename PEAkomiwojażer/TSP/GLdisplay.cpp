#include "Header.h"
/*************************************************************************************/
MatrixGraph graph;										// graf
vector <unsigned char> path;							// œcie¿ka
vector <vector <float>> vertices;						// wspó³rzêdne wierzcho³ków
double alfa;											// k¹t pomiêdzy wierzcho³kami
float Rmax = 7.0, Rmin = 5.0, Smin = 1e+30, Smax = 0;		// max i min promieñ, max i min suma d³ugoœci
vector <float> r;										// promienie
int n;													// liczba wierzcho³ków
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
	// wierzcho³ki na okrêgu oddalone o k¹t alfa w odleg³oœci od œrodka zale¿nej od œredniej d³ugoœci dróg od nich
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

	// ustalenie d³ugoœci promieni
	for (int i = 0; i < n; i++)
	{
		r[i] = (r[i] - Smin) / (Smax - Smin) * (Rmax - Rmin) + Rmin;
	}

	// ustelenie wspó³rzêdnych wierzcho³ków
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
	glClear(GL_COLOR_BUFFER_BIT);			// Czyszczenie okna aktualnym kolorem czyszcz¹cym

	//Axes();

	glColor3f(0.1f, 0.1f, 0.1f);			// Ustawienie aktualnego koloru rysowania na szary

	Prepare();								// przygotowanie wartoœci

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
	if (path.size() == graph.GetSize() + 1)								// rysowanie œcie¿ki
	{
		glColor3f(1.0f, 1.0f, 1.0f);		// Ustawienie aktualnego koloru rysowania na bia³y
		for (int i = 0; i < n; i++)
		{
			glBegin(GL_LINE_STRIP);
			glVertex2f(vertices[path[i]][0], vertices[path[i]][1]);
			glVertex2f(vertices[path[i + 1]][0], vertices[path[i + 1]][1]);
			glEnd();
		}
	}

	for (int i = 0; i < n; i++)				// rysowanie wierzcho³ków
	{
		Circle(vertices[i][0], vertices[i][1], 0.3, 20);
		float3 color = { 1.0f, 1.0f, 1.0f };
		string str = to_string(i + 1);
		float offset = str.length() * 0.045;
		RenderString(vertices[i][0] - offset, vertices[i][1] - 0.06, GLUT_BITMAP_HELVETICA_12, to_string(i + 1), color);
	}

	// rysowanie danych grafu:
	//   nazwa pliku
	//   optymalna œcie¿ka
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

	glFlush();								// Przekazanie poleceñ rysuj¹cych do wykonania
	glutSwapBuffers();
}

/*************************************************************************************/
void MyInit(void)
{
	// Kolor wnêtrza okna
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

/*************************************************************************************/
void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	GLfloat AspectRatio;									// Deklaracja zmiennej AspectRatio  okreœlaj¹cej proporcjê wymiarów okna
	if (vertical == 0)										// Zabezpieczenie przed dzieleniem przez 0
		vertical = 1;
	glViewport(0, 0, horizontal, vertical);					// Ustawienie wielkoœciokna okna widoku (viewport)
	glMatrixMode(GL_PROJECTION);							// Prze³¹czenie macierzy bie¿¹cej na macierz projekcji
	glLoadIdentity();										// Czyszcznie macierzy bie¿¹cej           
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;	// Wyznaczenie wspó³czynnika  proporcji okna
	if (horizontal <= vertical)
		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);
	else
		glOrtho(-7.5*AspectRatio, 7.5*AspectRatio, -7.5, 7.5, 10.0, -10.0);
	glMatrixMode(GL_MODELVIEW);								// Prze³¹czenie macierzy bie¿¹cej na macierz widoku modelu                                    
	glLoadIdentity();										// Czyszcenie macierzy bie¿¹cej
}

/*************************************************************************************/
//void keys(unsigned char key, int x, int y)
//{
//	if (key == 32) glutLeaveMainLoop(); // zamknij spacj¹
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
	// Ustawienie trybu wyœwietlania
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	// Rozmiar okna
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(800, 800);
	// Utworzenie okna i okreœlenie treœci napisu w nag³ówku okna
	glutCreateWindow("Graf");

	// Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹ (callback)
	glutDisplayFunc(RenderScene);
	// Dla aktualnego okna ustala funkcjê zwrotn¹ odpowiedzialn¹ za zmiany rozmiaru okna
	glutReshapeFunc(ChangeSize);
	// klawisze
	//glutKeyboardFunc(keys);
	// Inicjalizacja
	MyInit();
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	// Funkcja uruchamia szkielet biblioteki GLUT
	glutMainLoop();

}