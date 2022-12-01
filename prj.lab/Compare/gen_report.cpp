#include <hpdf.h>

void gen_report() {
	HPDF_Doc pdf = HPDF_New(0, 0);
	HPDF_Page page = HPDF_AddPage(pdf);
	HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", "CP1251");
	HPDF_Page_SetWidth(page, 400);
	HPDF_Page_SetHeight(page, 700);
	HPDF_Page_BeginText(page);
	HPDF_Page_SetFontAndSize(page, font, 14);
	HPDF_Page_MoveTextPos(page, 100, 670);
	HPDF_Page_ShowText(page, "Отчет об анализе работы двух решений задачи");
	HPDF_Page_EndText(page);
	HPDF_Image img = HPDF_LoadJpegImageFromFile(pdf, "process.jpg");
	HPDF_Page_DrawImage(page, img, 50, 400, 200, 200);

	HPDF_SaveToFile(pdf, "report_test.pdf");
}