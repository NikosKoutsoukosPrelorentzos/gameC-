#include "graphics.h"
#include "game.h"
#include "config.h"
// The custom callback function that the library calls 
// to check for and set the current application state.
void update(float ms)
{
   //thelw na lavw tin dieuthunsi tou mygame gia na tin xrisimopoiw

    Game* game = reinterpret_cast <Game*> (graphics::getUserData()); //enas void pointer thelei cast giaauto --> (Game*) alla gia na apofugw tin sugxusi
    game->update();


}

// The window content drawing function.
void draw()
{
    Game* game = reinterpret_cast <Game*> (graphics::getUserData());
    game->draw();
    


}
void resize(int w, int h)
{
    Game* game = reinterpret_cast<Game*>(graphics::getUserData());
    game->setWindowDimensions((unsigned int)w, (unsigned int)h);
}

int main()
{
    //game instance // uparxei auto to antikeimeno den einai null
    Game mygame;


    graphics::createWindow(WINDOW_WIDTH,WINDOW_HEIGHT, "Tutorial");

    //ksekiname apo edw
    graphics::setUserData(&mygame);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

     //prosarmozetai sto parathuro
    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    //prospathise na piasei megisti epifaneia xwris na to paramorfwseis
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    mygame.init();

    graphics::startMessageLoop();
    
    return 0;
} 