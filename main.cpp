#include<allegro5\allegro.h>
#include<math.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_image.h>
#include<allegro5\timer.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_font.h>
#include<allegro5\allegro_ttf.h>
#include<allegro5\keyboard.h>
#include<allegro5\allegro_audio.h>
#include<allegro5\allegro_acodec.h>
#include<allegro5\bitmap.h>
#include<allegro5\events.h>
const int row=5,col=5,tilew=100,tileh=100;
bool done=0;
int main()
{
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_acodec_addon();
	al_init_ttf_addon();
	al_install_audio();
	al_install_keyboard();
	al_init_primitives_addon();

	ALLEGRO_DISPLAY *display;
	//ALLEGRO_DISPLAY *display1;
	ALLEGRO_SAMPLE *sample=NULL;
	ALLEGRO_BITMAP *source=al_load_bitmap("c.jpg");
	ALLEGRO_BITMAP *image;
	ALLEGRO_FONT *font=al_load_font("PTC75F.ttf",30,0);
	ALLEGRO_BITMAP* tile[row*col];
	int arr[row*col];
	int empty=row*col-1;
	int tem;
	int count=0;
	ALLEGRO_BITMAP* temp;
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT_QUEUE* q=NULL;
	ALLEGRO_EVENT ev;

	sample=al_load_sample("sample.wav");
	image=al_create_bitmap(col*tilew,row*tileh);
	temp=al_create_bitmap(tilew,tileh);
	q=al_create_event_queue();
	timer=al_create_timer(0.02);
	display=al_create_display(col*tilew,row*tileh);
	al_reserve_samples(1);
	//display1=al_create_display(col*tilew,row*tileh);
	
	srand(time(NULL));
	al_register_event_source(q,al_get_keyboard_event_source());
	al_register_event_source(q,al_get_timer_event_source(timer));
	al_register_event_source(q,al_get_display_event_source(display));


	al_set_target_bitmap(image);
	al_draw_scaled_bitmap(source,0,0,al_get_bitmap_width(source),al_get_bitmap_height(source),0,0,col*tilew,row*tileh,0);
	al_set_target_bitmap(al_get_backbuffer(display));
	
	for(int i=0;i<(row*col);i++)
	{
	arr[i]=i;
	}


	for(int i=0;i<(row*col);i++)
	{
	tile[i]=al_create_bitmap(tilew,tileh);
	}

	for(int i=0;i<row*col-1;i++)
	{
		al_set_target_bitmap(tile[i]);
		al_draw_bitmap_region(image,(i*tilew)%(tilew*col),floor((i*1.0*tilew)/(tilew*col))*tileh,tilew,tileh,0,0,0);
		al_draw_rectangle(0,0,tilew,tileh,al_map_rgb(0,0,0),1);
	}
	al_set_target_bitmap(tile[row*col-1]);
	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_filled_rectangle(4,4,tilew,tileh,al_map_rgb(50,50,50));

	al_set_target_bitmap(al_get_backbuffer(display));
	
	al_clear_to_color(al_map_rgb(0,0,0));
	for(int i=0;i<(row*col);i++)
	{
	al_draw_bitmap(tile[i], (i*tilew)%(tilew*col),floor((i*1.0*tilew)/(tilew*col))*tileh,0);
	}
	al_flip_display();
	al_start_timer(timer);
	for(int i=0;i<row*col*10;i++)
	{
		al_wait_for_event(q,&ev);
		if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
			goto end;
		if(ev.type==ALLEGRO_EVENT_TIMER)
		{
			int t;
			t=rand()%4;
			switch(t)
			{
				
			case 1:
				if(empty%col!=col-1){
				temp=tile[empty+1];
				tem=arr[empty+1];
				tile[empty+1]=tile[empty];
				arr[empty+1]=arr[empty];
				tile[empty]=temp;
				arr[empty]=tem;
				empty++;
				al_play_sample(sample, 2.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
				}break;
			case 2:
				if(empty%col!=0){
				temp=tile[empty-1];
				tem=arr[empty-1];
				tile[empty-1]=tile[empty];
				arr[empty-1]=arr[empty];
				tile[empty]=temp;
				arr[empty]=tem;
				empty--;
				al_play_sample(sample, 2.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
				}break;
			case 3:
				if(empty<row*col-col){
				temp=tile[empty+col];
				tem=arr[empty+col];
				tile[empty+col]=tile[empty];
				arr[empty+col]=arr[empty];
				tile[empty]=temp;
				arr[empty]=tem;
				empty=empty+col;
				al_play_sample(sample, 2.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
				}break;
			case 0:
				if(empty>col-1){

				temp=tile[empty-col];
				tem=arr[empty-col];
				tile[empty-col]=tile[empty];
				arr[empty-col]=arr[empty];
				tile[empty]=temp;
				arr[empty]=tem;
				empty=empty-col;
				al_play_sample(sample, 2.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
				}break;
			}
		}
		for(int i=0;i<(row*col);i++)
		{
		al_draw_bitmap(tile[i], (i*tilew)%(tilew*col),floor((i*1.0*tilew)/(tilew*col))*tileh,0);
		}
		al_flip_display();
	}

		

	
	while(done==0)
	{

		al_wait_for_event(q,&ev);
		if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
		goto end;

		
	

		if(ev.type==ALLEGRO_EVENT_KEY_DOWN)
		{
			
			switch(ev.keyboard.keycode)
			{
			
			case ALLEGRO_KEY_LEFT:
				if(empty%col!=col-1){
				temp=tile[empty+1];
				tem=arr[empty+1];
				tile[empty+1]=tile[empty];
				arr[empty+1]=arr[empty];
				tile[empty]=temp;
				arr[empty]=tem;
				empty++;
				al_play_sample(sample, 2.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
				}
				
				break;
			case ALLEGRO_KEY_RIGHT:
				if(empty%col!=0){
				temp=tile[empty-1];
				tem=arr[empty-1];
				tile[empty-1]=tile[empty];
				arr[empty-1]=arr[empty];
				tile[empty]=temp;
				arr[empty]=tem;
				empty--;
				al_play_sample(sample, 2.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
				}break;
			case ALLEGRO_KEY_UP:
				if(empty<row*col-col){
				temp=tile[empty+col];
				tem=arr[empty+col];
				tile[empty+col]=tile[empty];
				arr[empty+col]=arr[empty];
				tile[empty]=temp;
				arr[empty]=tem;
				empty=empty+col;
				al_play_sample(sample, 2.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
				}break;
			case ALLEGRO_KEY_DOWN:
				if(empty>col-1){

				temp=tile[empty-col];
				tem=arr[empty-col];
				tile[empty-col]=tile[empty];
				arr[empty-col]=arr[empty];
				tile[empty]=temp;
				arr[empty]=tem;
				empty=empty-col;
				al_play_sample(sample, 2.0,0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
				}break;
				}
			}
		for(int i=0;i<(row*col);i++)
		{
		al_draw_bitmap(tile[i], (i*tilew)%(tilew*col),floor((i*1.0*tilew)/(tilew*col))*tileh,0);
		}
		al_flip_display();

		done=1;
		for(int i=0;i<row*col;i++)
		{
	
		if(arr[i]!=i)
			done=0;

		}
	}
	al_stop_timer(timer);
	timer=al_create_timer(0.5);
	al_register_event_source(q,al_get_timer_event_source(timer));
	al_start_timer(timer);




	while(1)
	{
		al_wait_for_event(q,&ev);
		if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
			goto end;
		if(ev.type==ALLEGRO_EVENT_TIMER)
		{
			int t;
			t=rand()%4;
			switch(t)
			{
				
			case 1:
				if(empty%col!=col-1){
				temp=tile[empty+1];
				tem=arr[empty+1];
				tile[empty+1]=tile[empty];
				arr[empty+1]=arr[empty];
				tile[empty]=temp;
				arr[empty]=tem;
				empty++;
				}break;
			case 2:
				if(empty%col!=0){
				temp=tile[empty-1];
				tem=arr[empty-1];
				tile[empty-1]=tile[empty];
				arr[empty-1]=arr[empty];
				tile[empty]=temp;
				arr[empty]=tem;
				empty--;
				}break;
			case 3:
				if(empty<row*col-col){
				temp=tile[empty+col];
				tem=arr[empty+col];
				tile[empty+col]=tile[empty];
				arr[empty+col]=arr[empty];
				tile[empty]=temp;
				arr[empty]=tem;
				empty=empty+col;
				}break;
			case 0:
				if(empty>col-1){

				temp=tile[empty-col];
				tem=arr[empty-col];
				tile[empty-col]=tile[empty];
				arr[empty-col]=arr[empty];
				tile[empty]=temp;
				arr[empty]=tem;
				empty=empty-col;
				}break;
			}
		}
		

		while(count<2)
		{
	
		al_wait_for_event(q,&ev);
		if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
		goto end;
		al_draw_bitmap(image, 0,0,0);
		al_draw_text(font,al_map_rgb(255,0,0),col*tilew/2,row*tileh/2-30,ALLEGRO_ALIGN_CENTRE,"You Are Done");
		al_flip_display();
		count++;
		
		}
		for(int i=0;i<(row*col);i++)
		{
		al_draw_bitmap(tile[i], (i*tilew)%(tilew*col),floor((i*1.0*tilew)/(tilew*col))*tileh,0);
		al_draw_text(font,al_map_rgb(255,0,0),col*tilew/2,row*tileh/2-30,ALLEGRO_ALIGN_CENTRE,"You Are Done");
		}
		al_flip_display();
	}





end:
	
	al_destroy_sample(sample);
    al_destroy_display(display);
	al_destroy_bitmap(source);
	al_destroy_bitmap(image);
	al_destroy_event_queue(q);
	al_destroy_timer(timer);
	al_destroy_font(font);
	for(int i=0;i<(row*col);i++)
	{
	al_destroy_bitmap(tile[i]);
	}
	
	return 0;
}


	