#include <algorithm>
#include <vector>
#include <ctime>

#include "Utils.h"
#include "Board.h"
#include "QuarterBoardHelper.h"

std::vector<Tile> Board::TILES = {
    Tile(RED, CIRCLE),
    Tile(RED, SQUARE),
    Tile(RED, TRIANGLE),
    Tile(RED, STAR),
    Tile(GREEN, CIRCLE),
    Tile(GREEN, SQUARE),
    Tile(GREEN, TRIANGLE),
    Tile(GREEN, STAR),
    Tile(BLUE, CIRCLE),
    Tile(BLUE, SQUARE),
    Tile(BLUE, TRIANGLE),
    Tile(BLUE, STAR),
    Tile(YELLOW, CIRCLE),
    Tile(YELLOW, SQUARE),
    Tile(YELLOW, TRIANGLE),
    Tile(YELLOW, STAR),
    Tile(RAINBOW, STAR)};

/* Constructors */
Board::Board()
    : quarterBoards{{QuarterBoard(0), QuarterBoard(1)}, {QuarterBoard(2), QuarterBoard(3)}}
{
}

/* Getters */
Frame Board::getFrame(int x, int y)
{
    /* Top left frame coordinates = (0,0) */
    int quarter_x = (x < 8) ? 0 : 1;
    int quarter_y = (y < 8) ? 0 : 1;
    return this->quarterBoards[quarter_x][quarter_y].getFrame(x % 8, y % 8);
}

/* Methods */
QuarterBoard Board::generateQuarterBoard(bool top, bool left)
{
    Frame frames[8][8];

    // Génerer les bordures
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            // Contours du plateau
            frames[i][j].setWall(top && j == 0, UP);
            frames[i][j].setWall(!top && j == 7, DOWN);
            frames[i][j].setWall(!left && i == 7, RIGHT);
            frames[i][j].setWall(left && i == 0, LEFT);

            // Carré du Centre
            if (top && left && i == 7 && j == 7)
                frames[i][j].setWall(1, UP);
            if (top && left && i == 7 && j == 6)
                frames[i][j].setWall(1, DOWN);
            if (top && left && i == 7 && j == 7)
                frames[i][j].setWall(1, LEFT);
            if (top && left && i == 6 && j == 7)
                frames[i][j].setWall(1, RIGHT);

            if (!top && left && i == 7 && j == 0)
                frames[i][j].setWall(1, LEFT);
            if (!top && left && i == 6 && j == 0)
                frames[i][j].setWall(1, RIGHT);
            if (!top && left && i == 7 && j == 0)
                frames[i][j].setWall(1, DOWN);
            if (!top && left && i == 7 && j == 1)
                frames[i][j].setWall(1, UP);

            if (!top && !left && i == 0 && j == 0)
                frames[i][j].setWall(1, DOWN);
            if (!top && !left && i == 0 && j == 1)
                frames[i][j].setWall(1, UP);
            if (!top && !left && i == 0 && j == 0)
                frames[i][j].setWall(1, RIGHT);
            if (!top && !left && i == 1 && j == 0)
                frames[i][j].setWall(1, LEFT);

            if (top && !left && i == 0 && j == 7)
                frames[i][j].setWall(1, UP);
            if (top && !left && i == 0 && j == 6)
                frames[i][j].setWall(1, DOWN);
            if (top && !left && i == 0 && j == 7)
                frames[i][j].setWall(1, RIGHT);
            if (top && !left && i == 1 && j == 7)
                frames[i][j].setWall(1, LEFT);
        }
    }

    // Générer les murs intérieurs
    // Quarter 1
    if (top && left)
    {
        // Murs colés à la bordures
        int k = 1 + getRandomNumber(5);
        frames[k - 1][0].setWall(1, RIGHT);
        frames[k][0].setWall(1, LEFT);

        int n = 1 + getRandomNumber(5);
        frames[0][n + 1].setWall(1, UP);
        frames[0][n].setWall(1, DOWN);
    }

    // Quarter 2
    if (top && !left)
    {
        int k = 1 + getRandomNumber(5);
        frames[k + 1][0].setWall(1, LEFT);
        frames[k][0].setWall(1, RIGHT);

        int n = 1 + getRandomNumber(5);
        frames[7][n + 1].setWall(1, UP);
        frames[7][n].setWall(1, DOWN);
    }

    // Quarter 3
    if (!top && left)
    {
        int k = 1 + getRandomNumber(5);
        frames[k - 1][7].setWall(1, RIGHT);
        frames[k][7].setWall(1, LEFT);

        int n = 1 + getRandomNumber(5);
        frames[0][n - 1].setWall(1, DOWN);
        frames[0][n].setWall(1, UP);
    }

    // Quarter 4
    if (!top && !left)
    {
        int k = 1 + getRandomNumber(5);
        frames[k + 1][7].setWall(1, LEFT);
        frames[k][7].setWall(1, RIGHT);

        int n = 1 + getRandomNumber(5);
        frames[7][n - 1].setWall(1, DOWN);
        frames[7][n].setWall(1, UP);
    }

    // Murs en angles à l'intérieurs
    std::vector<std::pair<int, int>> used_positions; // vecteur pour stocker les positions utilisées et les positions inutisables
    std::vector<std::pair<int, int>> corners;        // vecteur pour stocker les positions utilisées

    // Remplissage du vecteur used_position avec les cases en bordure de mur
    for (int i = 0; i < 8; ++i)
    {
        used_positions.push_back({i, 0}); // Mur du haut
        used_positions.push_back({i, 7}); // Mur du bas
        used_positions.push_back({0, i}); // Mur de gauche
        used_positions.push_back({7, i}); // Mur de droite
    }

    int max_corner = 4;
    // Rainbow Corner
    if ((this->rainbow_corner_quarter == 0 && top && left) ||
        (this->rainbow_corner_quarter == 1 && top && !left) ||
        (this->rainbow_corner_quarter == 2 && !top && left) ||
        (this->rainbow_corner_quarter == 3 && !top && !left))
    {
        max_corner = 5;
    }

    for (int i = 0; i < max_corner; i++)
    {
        int x, y;
        do
        {
            x = getRandomNumber(7);
            y = getRandomNumber(7);
        } while (std::count(used_positions.begin(), used_positions.end(), std::make_pair(x, y))); // Vérifie si la position est déjà utilisée

        used_positions.push_back({x, y}); // Marque la position comme utilisée
        corners.push_back({x, y});        // Marque la position comme utilisée
        // Marque les positions adjacentes comme utilisées
        used_positions.push_back({x + 1, y});
        used_positions.push_back({x - 1, y});
        used_positions.push_back({x, y + 1});
        used_positions.push_back({x, y - 1});
        used_positions.push_back({x + 1, y + 1});
        used_positions.push_back({x - 1, y - 1});
        used_positions.push_back({x + 1, y - 1});
        used_positions.push_back({x - 1, y + 1});

        // orientaion random of angle
        int orientation_of_angle = getRandomNumber(3); // 0: up-left, 1: up-right, 2: down-left, 3: down-right
        if (orientation_of_angle == 0)
        {
            frames[x][y].setWall(1, UP);
            frames[x][y].setWall(1, LEFT);
            frames[x - 1][y].setWall(1, RIGHT);
            frames[x][y - 1].setWall(1, DOWN);
        }
        else if (orientation_of_angle == 1)
        {
            frames[x][y].setWall(1, UP);
            frames[x][y].setWall(1, RIGHT);
            frames[x + 1][y].setWall(1, LEFT);
            frames[x][y - 1].setWall(1, DOWN);
        }
        else if (orientation_of_angle == 2)
        {
            frames[x][y].setWall(1, DOWN);
            frames[x][y].setWall(1, LEFT);
            frames[x - 1][y].setWall(1, RIGHT);
            frames[x][y + 1].setWall(1, UP);
        }
        else if (orientation_of_angle == 3)
        {
            frames[x][y].setWall(1, DOWN);
            frames[x][y].setWall(1, RIGHT);
            frames[x + 1][y].setWall(1, LEFT);
            frames[x][y + 1].setWall(1, UP);
        }

        // Setup Frame Tile
        frames[x][y].setTile(&Board::TILES[this->tile_index]);
        this->tile_index++;
    }

    return QuarterBoard(frames, 0);
}

void Board::generate()
{
    // Reset Tile indexing
    this->tile_index = 0;

    // Randomize Tile selection
    std::random_shuffle(Board::TILES.begin(), Board::TILES.end());

    // Randomize Rainbow Corner positionnement
    this->rainbow_corner_quarter = getRandomNumber(3);

    // Generate all QuarterBoards
    this->quarterBoards[0][0] = this->generateQuarterBoard(true, true);
    this->quarterBoards[0][1] = this->generateQuarterBoard(false, true);
    this->quarterBoards[1][0] = this->generateQuarterBoard(true, false);
    this->quarterBoards[1][1] = this->generateQuarterBoard(false, false);
}