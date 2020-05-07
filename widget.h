#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

const int BLOCK_SIZE=25;
const int MARGIN=5;
const int AREA_ROW=20;
const int AREA_COL=12;


enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SPACE
};


struct Border
{
    int ubound;
    int dbound;
    int lbound;
    int rbound;
};


struct block_point
{
    int pos_x;
    int pos_y;

};

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    void InitGame();
    void StartGame();
    void GameOver();

    void ResetBlock();
    void BlockMove(Direction dir);
    void BlockRotate(int block[4][4]);
    void CreateBlock(int block[4][4],int block_id);
    void GetBorder(int block[4][4],Border &border);
    void ConvertStable(int x,int y);
    bool IsCollide(int x,int y,Direction dir);

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    virtual void paintEvent(QPaintEvent *event);
    virtual void timerEvent(QTimerEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

private:
    Ui::Widget *ui;
    
private:
    int game_area[AREA_ROW][AREA_COL];
    block_point block_pos;
    int cur_block[4][4];
    Border cur_border;
    int next_block[4][4];
    bool isStable;
    int score;
    int game_timer;
    int paint_timer;
    int speed_ms;
    int refresh_ms;
};

#endif // WIDGET_H
