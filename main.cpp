#include <SFML/Graphics.hpp>
#include <ctime>
#include "string"
using namespace sf;

const int M = 24; // высота игрового поля
const int N = 13; // ширина игрового поля
int q = 0;
int field[M][N] = { 0 }; // игровое поле
bool flag = true;


// Массив фигурок-тетрамино
int figures[7][4] =
        {
                1,3,5,7, // I
                2,4,5,7, // Z
                3,5,4,6, // S
                3,5,4,7, // T
                2,3,5,7, // L
                3,5,7,6, // J
                2,3,4,5, // O
        };

struct Point
{
    int x, y;
} pPoint[4], p1Point[4];

// Проверка на выход за границы игрового поля
bool check()
{
    for (auto & i : pPoint) {
        if (i.x < 0 || i.x >= N || i.y >= M ) {
            if (i.y == M);
            return false;
        }
        else if (field[i.y][i.x]) {
             return false;}};
    return true;

};
bool check2() {
    for (auto & i : pPoint) {
        if (field[i.y][i.x]) {
            return false;}};
    return true;
}


int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(320, 480), "Tetris");
    // Создание и загрузка текстуры
    Texture texture, texture_background, texture_frame;
    texture.loadFromFile("/home/sad/Рабочий стол/test/image_2022-04-09_21-45-34.png");
    texture_background.loadFromFile("/home/sad/Рабочий стол/test/nyan-cat-gif-1.gif");

    Font font;
    font.loadFromFile("/home/sad/Рабочий стол/test/CyrilicOld.TTF");
    Text text("", font, 18);
    text.setColor(Color::Green);
    text.setPosition(207, 105);
    text.setStyle(Text::Bold);
    window.draw(text);
    Text timeText("", font, 18);
    timeText.setColor(Color::Green);
    text.setPosition(207, 130);


    // Создание спрайта
    Sprite sprite(texture), sprite_background(texture_background), sprite_frame(texture_frame);

    // Вырезаем из спрайта отдельный квадратик размером 18х18 пикселей
    sprite.setTextureRect(IntRect(0, 0, 18, 18));
    // Переменные для горизонтального перемещения и вращения
    int dx = 0; bool rotate = 0; int colorNum = 1; bool beginGame = true; int n = rand() % 7;

    // Переменные для таймера и задержки
    float timer = 0, delay = 0.3; int suka;

    // Часы (таймер)
    Clock clock;
    Clock clock1;
    Clock clock2;
    Clock clock3;


    // Главный цикл приложения. Выполняется, пока открыто окно
    while (window.isOpen())
    {
        // Получаем время, прошедшее с начала отсчета, и конвертируем его в секунды
//        if (qqq % 2 )texture_background.loadFromFile("/home/sad/Рабочий стол/test/nyan-cat-gif-1.gif");
//        texture_background.loadFromFile("/home/sad/Рабочий стол/test/image_2022-04-09_21-45-34.png");

        float time = clock.getElapsedTime().asSeconds();
        int qqq = clock1.getElapsedTime().asSeconds();
        int newTime = clock2.getElapsedTime().asSeconds();
        float timerForChangeBackGround = clock3.getElapsedTime().asMilliseconds();
        clock.restart();
        timer += time;
        suka += qqq;
        // Обрабатываем очередь событий в цикле
        Event event{};

        while (window.pollEvent(event))
        {
            // Пользователь нажал на «крестик» и хочет окно закрыть?
            if (event.type == Event::Closed)
                // тогда закрываем его
                window.close();

            // Была нажата кнопка на клавиатуре?
            if (event.type == Event::KeyPressed)
                // Эта кнопка – стрелка вверх?…
                if (event.key.code == Keyboard::Up) rotate = true;
                    // …или же стрелка влево?…
                else if (event.key.code == Keyboard::Left) dx = -1;
                    // …ну тогда может это стрелка вправо?
                else if (event.key.code == Keyboard::Right) dx = 1;
        }
        auto newDelay = delay;
        // Нажали кнопку "вниз"? Ускоряем падение тетрамино
        if (Keyboard::isKeyPressed(Keyboard::Down)) delay /= 3;

        //// Горизонтальное перемещение ////
        for (int i = 0; i < 4; i++) { p1Point[i] = pPoint[i]; pPoint[i].x += dx; }

        // Вышли за пределы поля после перемещения? Тогда возвращаем старые координаты
        if (!check()) for (int i = 0; i < 4; i++) pPoint[i] = p1Point[i];
        if (flag)
        if (!check2()) for (int i = 0; i < 4; i++)  { flag = false;  }


        //// Вращение ////
        if (rotate)
        {
            Point p = pPoint[1]; // задаем центр вращения
            for (auto & i : pPoint)
            {
                int x = i.y - p.y; //y-y0
                int y = i.x - p.x; //x-x0
                i.x = p.x - x;
                i.y = p.y + y;
            }
            // Вышли за пределы поля после поворота? Тогда возвращаем старые координаты
            if (!check()) { for (int i = 0; i < 4; i++) pPoint[i] = p1Point[i];
            }

        }

        //// Движение тетрамино вниз (Тик таймера) ////
        if (timer > delay)
        {



            for (int i = 0; i < 4; i++) { p1Point[i] = pPoint[i]; pPoint[i].y += 1; }
            if (!check())
            {
                for (auto & i : p1Point) field[i.y][i.x] = colorNum;
                colorNum = 1 + rand() % 7;
                n = rand() % 7;
                for (int i = 0; i < 4; i++)
                {
                    pPoint[i].x = figures[n][i] % 2;
                    pPoint[i].y = figures[n][i] / 2;
                }

            }
            timer = 0;

        }

        //----ПРОВЕРКА ЛИНИИ----//
        int k = M - 1;
        for (int i = M - 1; i > 0; i--)
        {
            int count = 0;
            for (int j = 0; j < N; j++)
            {
                if (field[i][j]) count++;
                if (field[k][j] != field[i][j]) {
                    q ++;
                    std::string counter = std::to_string(q);
                    text.setString("your score" + counter);

                };
                field[k][j] = field[i][j];
                if (!flag) {field[i][j] = 0;}

            }
            if (count < N) {k--;

           }
        }

        // Первое появление тетрамино на поле?
        if (beginGame)
        {
            beginGame = false;
            n = rand() % 7;
            for (int i = 0; i < 4; i++)
            {
                pPoint[i].x = figures[n][i] % 2;
                pPoint[i].y = figures[n][i] / 2;
            }
        }
        dx = 0; rotate = false; delay = newDelay;
        if (newTime == 100) {delay /= 1.5; clock2.restart();}

        //----ОТРИСОВКА----//
        // Задаем цвет фона - белый
        window.clear(Color::Black);
        window.draw(sprite_background);
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
            {
                if (field[i][j] == 0) continue;
                sprite.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
                sprite.setPosition(j * 18, i * 18);
                sprite.move(2 , 47); // смещение
                window.draw(sprite);
            }

        for (auto & i : pPoint)
        {
            // Разукрашиваем тетрамино
            sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));

            // Устанавливаем позицию каждого кусочка тетрамино
            sprite.setPosition(i.x * 18, i.y * 18);

            sprite.move(2, 47); // смещение

            // Отрисовка спрайта
            if (flag) window.draw(sprite);
            else {
                window.clear();
                Text textLoose("you loose \n your score:", font, 60);
                textLoose.setColor(Color::Red);
                textLoose.setPosition(16, 160);
                textLoose.setStyle(Text::Bold);
                window.draw(textLoose);
                std::string counter = std::to_string(q);
                text.setColor(Color::Red);
                text.setString(counter);
                text.setPosition(270, 300);
                clock1.getElapsedTime();
            }
        }
        // Отрисовка фрейма
        if (flag)
        text.setPosition(209, 50);
        window.draw(text);
        window.draw(sprite_frame);
        if (flag)
        timeText.setString("your time:" + std::to_string(qqq));
        timeText.setPosition(211, 30);
        window.draw( timeText);
//        if (timerForChangeBackGround == 1) texture_background.loadFromFile("/home/sad/Рабочий стол/test/ade5d0eb87be4402ae77e8d7b4a77acf0btpmsNyO91VNo9l-0.png");
//        if (timerForChangeBackGround == 20) texture_background.loadFromFile("/home/sad/Рабочий стол/test/ade5d0eb87be4402ae77e8d7b4a77acf0btpmsNyO91VNo9l-2.png");
//        if (timerForChangeBackGround == 30) texture_background.loadFromFile("/home/sad/Рабочий стол/test/ade5d0eb87be4402ae77e8d7b4a77acf0btpmsNyO91VNo9l-8.png");
//        if (timerForChangeBackGround == 30) texture_background.loadFromFile("/home/sad/Рабочий стол/test/ade5d0eb87be4402ae77e8d7b4a77acf0btpmsNyO91VNo9l-3.png");
//        if (timerForChangeBackGround == 40) texture_background.loadFromFile("/home/sad/Рабочий стол/test/ade5d0eb87be4402ae77e8d7b4a77acf0btpmsNyO91VNo9l-4.png");
//        if (timerForChangeBackGround == 50) texture_background.loadFromFile("/home/sad/Рабочий стол/test/ade5d0eb87be4402ae77e8d7b4a77acf0btpmsNyO91VNo9l-5.png");
//        if (timerForChangeBackGround == 60) texture_background.loadFromFile("/home/sad/Рабочий стол/test/ade5d0eb87be4402ae77e8d7b4a77acf0btpmsNyO91VNo9l-6.png");
//        if (timerForChangeBackGround == 70) texture_background.loadFromFile("/home/sad/Рабочий стол/test/ade5d0eb87be4402ae77e8d7b4a77acf0btpmsNyO91VNo9l-7.png");
//        if (timerForChangeBackGround == 80) texture_background.loadFromFile("/home/sad/Рабочий стол/test/ade5d0eb87be4402ae77e8d7b4a77acf0btpmsNyO91VNo9l-8.png");
//        if (timerForChangeBackGround == 90) texture_background.loadFromFile("/home/sad/Рабочий стол/test/ade5d0eb87be4402ae77e8d7b4a77acf0btpmsNyO91VNo9l-9.png");
//        if (timerForChangeBackGround == 100) texture_background.loadFromFile("/home/sad/Рабочий стол/test/ade5d0eb87be4402ae77e8d7b4a77acf0btpmsNyO91VNo9l-10.png");
//        if (timerForChangeBackGround == 110) texture_background.loadFromFile("/home/sad/Рабочий стол/test/ade5d0eb87be4402ae77e8d7b4a77acf0btpmsNyO91VNo9l-11.png");

//        if (timerForChangeBackGround > 31) clock3.restart();
texture_background.loadFromFile("/home/sad/Рабочий стол/test/newNen");
        // Отрисовка окна
        window.display();
    }

    return 0;
}
