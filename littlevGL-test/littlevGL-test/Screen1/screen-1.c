  
/*********************
   *      INCLUDES
   *********************/
#include "screen-1.h"

   /*********************
    *      DEFINES
    *********************/

    /**********************
     *      TYPEDEFS
     **********************/

     /**********************
      *  STATIC PROTOTYPES
      **********************/

static void create_tab1(lv_obj_t* parent);
static void create_tab2(lv_obj_t* parent);
static void btn_event_cb(lv_obj_t* btn, lv_event_t event);
static void change_style(lv_obj_t* btn, lv_event_t event);
static void decrease_slider(lv_obj_t* btn, lv_event_t event);
static void increase_slider(lv_obj_t* btn, lv_event_t event);
static void toggle_button_availability(lv_obj_t* btn, lv_event_t event);
static void update_buttons_slider_cb(lv_obj_t* sl, lv_event_t event);
static void update_button_availability();

/**********************
 *  STATIC VARIABLES
 **********************/

static lv_obj_t* slider;
static lv_style_t changing_style;

/**********************
 *      MACROS
 **********************/

int i = 0;
bool color_change = false;
bool is_active = true;
lv_obj_t* lb;
lv_obj_t* btn_minus;
lv_obj_t* btn_plus;
lv_obj_t* labelONOFF;
lv_obj_t* btn_toggle;

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void create_screen1(void)
{
    lv_obj_t* scr = lv_disp_get_scr_act(NULL);     /*Get the current screen*/
    lv_disp_load_scr(scr);

    lv_obj_t* tv = lv_tabview_create(scr, NULL);
    lv_obj_set_size(tv, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_tabview_set_sliding(tv, false);


    /***********************
     * TABS
     ***********************/

    lv_obj_t* tab1 = lv_tabview_add_tab(tv, "Tab 1");
    lv_obj_t* tab2 = lv_tabview_add_tab(tv, "Tab 2");

    create_tab1(tab1);
    create_tab2(tab2);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void btn_event_cb(lv_obj_t* btn, lv_event_t event)
{
    const char* strings[] = { "one","two","three", "four", "five" };

    if (event == LV_EVENT_RELEASED)
    {
        /* shift trhough labels with every click */
        i++;
        if (i > 4)
            i = 0;

        lv_label_set_text(lb, strings[i]);
    }
}

static void change_style(lv_obj_t* btn, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        color_change = !color_change;

        if (color_change)
        {
            changing_style.body.main_color = LV_COLOR_GREEN;
            changing_style.body.grad_color = LV_COLOR_GREEN;
            lv_obj_set_style(btn, &changing_style);
        }
        else
        {
            changing_style.body.main_color = LV_COLOR_BLUE;
            changing_style.body.grad_color = LV_COLOR_BLUE;
            lv_obj_set_style(btn, &changing_style);
        }
    }
}

static void decrease_slider(lv_obj_t* btn, lv_event_t event)
{
    int value = lv_slider_get_value(slider);

    if (event == LV_EVENT_RELEASED)
    {
        if (value > lv_slider_get_min_value(slider))
        {
            value--;
            lv_slider_set_value(slider, value, true);
            update_button_availability();
        }
    }
}

static void increase_slider(lv_obj_t* btn, lv_event_t event)
{
    int value = lv_slider_get_value(slider);

    if (event == LV_EVENT_RELEASED)
    {
        if (value < lv_slider_get_max_value(slider))
        {
            value++;
            lv_slider_set_value(slider, value, true);
            update_button_availability();
        }
    }
}

static void update_button_availability()    /* makes btn_minus and btn_plus available or unavailable to click, depending on the position of the slider */
{
    int value = lv_slider_get_value(slider);

    if (value == lv_slider_get_min_value(slider))
    {
        lv_btn_set_state(btn_minus, LV_BTN_STATE_INA);
        lv_btn_set_state(btn_plus, LV_BTN_STATE_REL);
        lv_obj_set_click(btn_minus, false);
        lv_obj_set_click(btn_plus, true);
    }
    else if (value == lv_slider_get_max_value(slider))
    {
        lv_btn_set_state(btn_minus, LV_BTN_STATE_REL);
        lv_btn_set_state(btn_plus, LV_BTN_STATE_INA);
        lv_obj_set_click(btn_minus, true);
        lv_obj_set_click(btn_plus, false);
    }
    else
    {
        lv_btn_set_state(btn_minus, LV_BTN_STATE_REL);
        lv_btn_set_state(btn_plus, LV_BTN_STATE_REL);
        lv_obj_set_click(btn_minus, true);
        lv_obj_set_click(btn_plus, true);
    }

}

static void update_buttons_slider_cb(lv_obj_t* sl, lv_event_t event)    /* called to update button availability when the slider is dragged */
{
    if (event == LV_EVENT_VALUE_CHANGED)
    {
        update_button_availability();
    }
}

static void toggle_button_availability(lv_obj_t* btn, lv_event_t event) /* A button that enables or disables the clicking of the slider, btn_plus and btn_minus */
{
    if (event == LV_EVENT_RELEASED)
    {
        if (!is_active)
        {
            update_button_availability();
            lv_obj_set_click(slider, true);
            lv_label_set_text(labelONOFF, "ON");
        }
        else
        {
            lv_btn_set_state(btn_minus, LV_BTN_STATE_INA);
            lv_btn_set_state(btn_plus, LV_BTN_STATE_INA);
            lv_obj_set_click(btn_minus, false);
            lv_obj_set_click(btn_plus, false);
            lv_obj_set_click(slider, false);
            lv_label_set_text(labelONOFF, "OFF");
        }

        is_active = !is_active;
    }
}

static void create_tab1(lv_obj_t* parent)
{
    lv_obj_t* scr = lv_disp_get_scr_act(NULL);
    lv_obj_t* label1 = lv_label_create(NULL, NULL);

     /***********************
      * STYLE
      ***********************/

    lv_style_copy(&changing_style, &lv_style_plain);
    changing_style.body.main_color = LV_COLOR_RED;
    changing_style.body.grad_color = LV_COLOR_RED;
    changing_style.body.radius = 3;

    static lv_style_t h_style;
    lv_style_copy(&h_style, &lv_style_plain);
    h_style.body.padding.inner = LV_DPI / 10;
    h_style.body.padding.left = LV_DPI / 4;
    h_style.body.padding.right = LV_DPI / 4;
    h_style.body.padding.top = LV_DPI / 10;
    h_style.body.padding.bottom = LV_DPI / 10;

    lv_obj_t* h = lv_cont_create(parent, NULL);     /* create a container for objects */
    lv_obj_set_style(h, &h_style);
    lv_obj_set_click(h, false);
    lv_cont_set_fit(h, LV_FIT_TIGHT);
    lv_cont_set_layout(h, LV_LAYOUT_COL_M);

    /***********************
     * BUTTONS
     ***********************/

    lv_obj_t* btn1 = lv_btn_create(h, NULL); /*Create a button on the container h*/

    if (NULL == lb)
        lb = lv_label_create(btn1, NULL);
    lv_label_set_text(lb, "one");

    lv_obj_set_event_cb(btn1, btn_event_cb);
    lv_obj_set_size(btn1, lv_obj_get_width(scr) / 3, 50);
    lv_obj_align(btn1, label1, LV_ALIGN_IN_TOP_MID, 0, 30);

    // Colour changing button

    lv_obj_t* btn_flashing = lv_btn_create(h, NULL);
    lv_obj_set_pos(btn_flashing, 10, 10);
    lv_obj_set_style(btn_flashing, &changing_style);
    label1 = lv_label_create(btn_flashing, NULL);
    lv_label_set_text(label1, "I change colour");
    lv_obj_set_event_cb(btn_flashing, change_style);

    // Toggle availability of the slider and the +- buttons

    btn_toggle = lv_btn_create(h, NULL);
    lv_obj_align(btn_toggle, btn1, LV_ALIGN_IN_RIGHT_MID, 120, 20);
    lv_obj_set_size(btn_toggle, 30, 30);
    lv_obj_set_event_cb(btn_toggle, toggle_button_availability);
    labelONOFF = lv_label_create(btn_toggle, NULL);
    lv_label_set_text(labelONOFF, "ON");

    /***********************
     * SLIDER
     ***********************/

    slider = lv_slider_create(h, NULL);                            /*Create a slider*/
    lv_obj_set_size(slider, lv_obj_get_width(h) / 3, LV_DPI / 5);            /*Set the size*/
    lv_obj_align(slider, btn1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);               /*Align below the first button*/
    lv_slider_set_range(slider, 0, 5);
    lv_slider_set_value(slider, 0, false);
    lv_obj_set_event_cb(slider, update_buttons_slider_cb);

    // Slider +- buttons

    btn_minus = lv_btn_create(h, NULL);
    lv_obj_set_size(btn_minus, LV_DPI / 3, LV_DPI / 3);
    lv_obj_align(btn_minus, slider, LV_ALIGN_IN_LEFT_MID, -60, 0);
    label1 = lv_label_create(btn_minus, NULL);
    lv_label_set_text(label1, "-");
    lv_obj_set_event_cb(btn_minus, decrease_slider);

    btn_plus = lv_btn_create(h, NULL);
    lv_obj_set_size(btn_plus, LV_DPI / 3, LV_DPI / 3);
    lv_obj_align(btn_plus, slider, LV_ALIGN_IN_RIGHT_MID, 60, 0);
    label1 = lv_label_create(btn_plus, NULL);
    lv_label_set_text(label1, "+");
    lv_obj_set_event_cb(btn_plus, increase_slider);

    update_button_availability();
}

static void create_tab2(lv_obj_t* parent)
{
    /***********************
     * STYLE
     ***********************/

    lv_obj_t* scr = lv_disp_get_scr_act(NULL);

    static lv_style_t h_style;
    lv_style_copy(&h_style, &lv_style_plain);
    h_style.body.padding.inner = LV_DPI / 10;
    h_style.body.padding.left = LV_DPI / 4;
    h_style.body.padding.right = LV_DPI / 4;
    h_style.body.padding.top = LV_DPI / 10;
    h_style.body.padding.bottom = LV_DPI / 10;

    lv_obj_t* h = lv_cont_create(parent, NULL);
    lv_obj_set_style(h, &h_style);
    lv_obj_set_click(h, false);
    lv_cont_set_fit(h, LV_FIT_TIGHT);
    lv_cont_set_layout(h, LV_LAYOUT_COL_M);

    static const char* btnm_str[] = { "1", "2", "3", LV_SYMBOL_OK, LV_SYMBOL_CLOSE, "" };
    lv_obj_t* btnm = lv_btnm_create(h, NULL);
    lv_obj_set_size(btnm, lv_disp_get_hor_res(NULL) / 2, 2 * LV_DPI / 3);
    lv_obj_align(btnm, scr, LV_ALIGN_CENTER, 0, 0);
    lv_btnm_set_map(btnm, btnm_str);
    lv_btnm_set_btn_ctrl_all(btnm, LV_BTNM_CTRL_TGL_ENABLE);
    lv_btnm_set_one_toggle(btnm, true);
}
