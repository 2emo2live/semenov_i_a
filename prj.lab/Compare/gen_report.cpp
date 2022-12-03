#include <hpdf.h>
#include <string>
#include <fstream>

HPDF_Doc pdf = HPDF_New(0, 0);
HPDF_Page page = HPDF_AddPage(pdf);
HPDF_Page page2 = HPDF_AddPage(pdf);
HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", "CP1251");
int height = 700, width = 500;


void print_text(const char* c, int x, int y, HPDF_Page page) {
	HPDF_Page_BeginText(page);
	HPDF_Page_SetFontAndSize(page, font, 14);
	HPDF_Page_MoveTextPos(page, x, y);
	HPDF_Page_ShowText(page, c);
	HPDF_Page_EndText(page);
}

int print_pictures(int y0, std::vector<int> steps, HPDF_Page page, int start) {
	int x0 = 30, x1 = 250;
	for (int i = start; i < steps.size(); i++) {
		if (y0 < 20) {
			return i;
		}
		std::string name = "input" + std::to_string(steps[i]) + ".jpg";
		HPDF_Image img = HPDF_LoadJpegImageFromFile(pdf, name.c_str());
		HPDF_Page_DrawImage(page, img, x0, y0, 200, 200);
		name = "process" + std::to_string(steps[i]) + ".jpg";
		img = HPDF_LoadJpegImageFromFile(pdf, name.c_str());
		HPDF_Page_DrawImage(page, img, x1, y0, 200, 200);
		y0 -= 220;
	}
	return -1;
}

void gen_report(std::vector<int> steps) {
	HPDF_Page_SetWidth(page, width);
	HPDF_Page_SetHeight(page, height);
	HPDF_Page_SetWidth(page2, width);
	HPDF_Page_SetHeight(page2, height);

	std::ifstream f("rep_begin.txt");
	std::string s;
	int x = 100, y = height - 30;
	getline(f, s);
	print_text(s.c_str(), x, y, page);
	x = 50;
	y = 630;
	getline(f, s);
	print_text(s.c_str(), x, y, page);
	x = 30;
	y -= 15;
	while (getline(f, s)) {
		print_text(s.c_str(), x, y, page);
		y -= 15;
	}
	//std::cout << y - 220 << ' ';
	int n = print_pictures(y - 220, steps, page, 0);
	//std::cout << n;
	if (n != -1)
		int n2 = print_pictures(height - 220, steps, page2, n);

	y = height - 220 *(steps.size() - n) - 30;
	std::ifstream f_end("rep_conclude.txt");
	while (getline(f_end, s)) {
		print_text(s.c_str(), x, y, page2);
		y -= 15;
	}

	HPDF_SaveToFile(pdf, "report_test.pdf");
}