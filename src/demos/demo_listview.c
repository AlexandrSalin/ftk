#include "ftk.h"

#include "ftk_list_view.h"
#include "ftk_list_render_default.h"
#include "ftk_list_model_default.h"

#define IDC_TEST_BUTTON 1000
int g_index = 0;
FtkBitmap*  left_icon = NULL;
FtkBitmap* right_icon = NULL;

static Ret button_quit_clicked(void* ctx, void* obj)
{
	ftk_quit();

	return RET_OK;
}

static Ret button_more_clicked(void* ctx, void* obj)
{
	int i = 0;
	char text[32] = {0};
	FtkListItemInfo info = {0};
	FtkListModel* model = ctx;

	for(i = 0; i < 4; i++)
	{
		g_index++;
		snprintf(text, sizeof(text), "item%04d", g_index);
		info.text = strdup(text);
		info.left_icon = left_icon;
		info.right_icon = right_icon;
		info.type = g_index%4;
		ftk_list_model_add(model, &info);
	}

	return RET_OK;
}

static void on_window_close(void* user_data)
{
	ftk_quit();

	return ;
}

void item_destroy(FtkListItemInfo* info)
{

	return;
}

Ret on_item_clicked(void* ctx, void* list)
{
	FtkListItemInfo* info = NULL;
	FtkListModel* model = ftk_list_view_get_model(list);
	int i = ftk_list_view_get_selected(list);

	ftk_list_model_get_data(model, i, &info);
	if(info != NULL)
	{
		info->state = !info->state;
	}
	ftk_logd("%s: %d/%d\n", __func__, 
		ftk_list_view_get_selected(list),
		ftk_list_model_get_total(model));

	return RET_OK;
}

int main(int argc, char* argv[])
{
	int width = 0;
	int height = 0;
	char text[32] = {0};
	FtkWidget* win = NULL;
	FtkWidget* button = NULL;
	FtkWidget* list = NULL;
	FtkListModel* model = NULL;
	FtkListRender* render = NULL;
	FtkListItemInfo info = {0};

	ftk_init(argc, argv);
	
	win = ftk_app_window_create();
	width = ftk_widget_width(win);
	height = ftk_widget_height(win);
	
	list = ftk_list_view_create(win, 10, 5, width - 20, 3 * height/4-5);
	ftk_list_view_set_clicked_listener(list, on_item_clicked, NULL);

	model = ftk_list_model_default_create(10, item_destroy);
	render = ftk_list_render_default_create();
	left_icon = ftk_bitmap_factory_load(ftk_default_bitmap_factory(), TESTDATA_DIR"/alarm"FTK_STOCK_IMG_SUFFIX);
	right_icon = ftk_bitmap_factory_load(ftk_default_bitmap_factory(), TESTDATA_DIR"/search"FTK_STOCK_IMG_SUFFIX);

	g_index = 0;
	for(g_index = 0; g_index < 4; g_index++)
	{
		snprintf(text, sizeof(text), "item%04d", g_index);
		info.text = strdup(text);
		info.left_icon = left_icon;
		info.right_icon = right_icon;
		info.type = g_index%4;
		ftk_list_model_add(model, &info);
	}

	ftk_list_view_init(list, model, render, 40);

	button = ftk_button_create(win, width/4, 3 * height/4 + 5, width/4, 60);
	ftk_widget_set_text(button, "more");
	ftk_button_set_clicked_listener(button, button_more_clicked, model);

	button = ftk_button_create(win, width/2, 3 * height/4 + 5, width/4, 60);
	ftk_widget_set_text(button, "quit");
	ftk_button_set_clicked_listener(button, button_quit_clicked, win);
	ftk_window_set_focus(win, button);

	ftk_widget_set_text(win, "button demo");
	ftk_widget_show_all(win, 1);
	ftk_widget_set_user_data(win, on_window_close, win);

	ftk_run();

	return 0;
}
