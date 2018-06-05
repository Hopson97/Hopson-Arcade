//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by SpaceInvaders.rc
//
#define IDI_ICON1                       102

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        103
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1001
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif

#include <unordered_map>
#include <string>

/**
    Holds all the resources of the game
*/
template<typename Resource>
class ResourceManager
{
    public:
        ResourceManager (const std::string& folder, const std::string& extention)
        :   m_folder    ("res/" + folder + "/")
        ,   m_extention ("." + extention)
        { }

        const Resource& get(const std::string& name)
        {
            if (!exists(name)) {
                add(name);
            }

            return m_resources.at(name);
        }

        bool exists(const std::string& name) const
        {
            return m_resources.find(name) != m_resources.end();
        }

        void add(const std::string& name)
        {
            Resource r;

            //if the resource fails to load, then it adds a default "fail" resource
            if(!r.loadFromFile(getFullFilename(name))) {
                Resource fail;
                fail.loadFromFile(m_folder + "_fail_" + m_extention);
                m_resources.insert(std::make_pair(name, fail));
            }
            else {
                m_resources.insert(std::make_pair(name, r));
            }
        }

    private:
        std::string getFullFilename(const std::string& name)
        {
            return m_folder + name + m_extention;
        }

        const std::string m_folder;
        const std::string m_extention;

        std::unordered_map<std::string, Resource> m_resources;
};

#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
    public:
        struct Frame
        {
            Frame(const sf::IntRect& bnds, sf::Time dly)
            :   bounds  (bnds)
            ,   delay   (dly) {}

            sf::IntRect bounds; //The area in a texture of the frame
            sf::Time    delay;  //Time delay to next frame
        };

        Animation(unsigned frameWidth, unsigned frameHeight);

        void addFrame(unsigned index, sf::Time delay);

        const sf::IntRect& getFrame();

    private:
        sf::Clock m_timer;              //Timer for progressing the animation

        std::vector<Frame> m_frames;    //List of animation frames

        unsigned m_framePointer = 0;    //The index of the current active frame
        const unsigned FRAME_WIDTH; 
        const unsigned FRAME_HEIGHT;      

};

#include <string>

std::string getFileContent(const std::string& filePath, bool throws);

#include <SFML/Graphics.hpp>

class FPSCounter
{
    public:
        FPSCounter();

        void update();

        void draw(sf::RenderTarget& renderer);

    private:
        sf::Text m_text;
        sf::Font m_font;

        sf::Clock m_delayTimer;
        sf::Clock m_fpsTimer;

        float m_fps = 0;

        int m_frameCount = 0;
};

constexpr float PI = 3.14159265f;
constexpr float MIN_PI = 3.14f;

template <typename T>
T toRadians(T degrees)
{
    return degrees * PI / 180;
}

template <typename T>
T toDegrees(T radians)
{
    return (radians * 180) / PI;
}

struct NonCopyable
{
    NonCopyable() = default;
    NonCopyable& operator = (const NonCopyable&) = delete;
    NonCopyable(const NonCopyable&) = delete;
};


struct NonMovable
{
    NonMovable() = default;
    NonMovable& operator = (NonCopyable&&) = delete;
    NonMovable(NonCopyable&&) = delete;
};

#include <random>
#include <ctime>

template <typename Engine = std::mt19937>
class Random
{
    template<typename T>
    using UniformDist = std::uniform_real_distribution<T>;
    using UniformIntDist = std::uniform_int_distribution<int>;

    public:
        static Random gRand;

        Random(int seed = std::time(nullptr))
        :   m_prng  (seed)
        { }

        int getIntInRange(int low, int high)
        {
            return getNumberInRange<UniformIntDist>(low, high);
        }

        float getFloatInRange(float low, float high)
        {
            return getNumberInRange<UniformDist<float>>(low, high);
        }

        template<typename T>
        T getNumberInRange(T low, T high)
        {
            return getNumberInRange<UniformDist<T>>(low, high);
        }

        template<typename Dist, typename T>
        T getNumberInRange(T low, T high)
        {
            Dist dist(low, high);
            return dist(m_prng);
        }

    private:
        Engine m_prng;
};

#include <SFML/Graphics.hpp>

class ToggleKey
{
    public:
        ToggleKey(sf::Keyboard::Key);

        bool isKeyPressed();

    private:
        sf::Keyboard::Key m_key;
        sf::Clock m_delayTimer;
};

#include <SFML/Graphics.hpp>

namespace SpaceInvaders
{
    /*
        Utility class for rendering a large number of entites which share
        the same animation
    */
    class AnimationRenderer
    {
    public:
        AnimationRenderer(int frameWidth, int frameHeight,
            float entityWidth, float entityHeight,
            const sf::Texture& spriteSheet);

        //Changes to the next frame
        void nextFrame();

        //Renders a single entity, using the current animation frame
        void renderEntity(sf::RenderTarget& renderer, int type, const sf::Vector2f& position);

    private:
        sf::RectangleShape m_entity;
        int m_currentFrame;
        const int m_frameWidth;
        const int m_frameHeight;
    };
}

#include <SFML/Graphics.hpp>

namespace SpaceInvaders
{
    class Collidable
    {
    public:
        Collidable(float width, float height);

        bool tryCollideWith(Collidable& other);
        sf::FloatRect getBox() const;

        virtual const sf::Vector2f& getPosition() const = 0;
        virtual void onCollide(Collidable& other) = 0;

    private:
        sf::Vector2f m_size;
    };
}

namespace Display 
{
    constexpr unsigned WIDTH = 1000;
    constexpr unsigned HEIGHT = 800;
}

#include <SFML/Graphics.hpp>

namespace SpaceInvaders
{
    /*
        Represents a single explosion entity
    */
    class Explosion
    {
    public:
        Explosion(const sf::Vector2f& position);

        bool isLifeOver() const;
        const sf::Vector2f& getPosition() const;

    private:
        sf::Vector2f m_position;        //The position of the explosion
        sf::Clock m_lifetimeCounter;    //Clock for checking if the explosion is outlived
    };
}

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class ResourceHolder : public NonCopyable, public NonMovable
{
    public:
        static ResourceHolder& get();

        ResourceManager<sf::Font>           fonts;
        ResourceManager<sf::Texture>        textures;
        ResourceManager<sf::SoundBuffer>    soundBuffers;

    private:
        ResourceHolder();
};

#include <SFML/Graphics.hpp>
#include <memory>

namespace gui
{
    class Widget
    {
        public:
            virtual void handleEvent(sf::Event e, const sf::RenderWindow& window) = 0;

            virtual void render(sf::RenderTarget& renderer) = 0;

            virtual void setPosition(const sf::Vector2f& pos) = 0;

            virtual sf::Vector2f getSize() const = 0;

            class Text : public sf::Text
            {
                public:
                    Text();
            };

            class Rectangle : public sf::RectangleShape
            {
                public:
                    bool isRolledOn (const sf::RenderWindow& window) const;
                    bool isClicked  (sf::Event, const sf::RenderWindow& window);
            };
    };
}


#include <functional>


namespace gui
{
    enum class ButtonSize
    {
        Small,
        Wide,
    };

    class Button : public gui::Widget
    {
        public:
            Button(ButtonSize s = ButtonSize::Wide);

            void setFunction(std::function<void(void)> func);
            void setText    (const std::string& str);
            void setTexture (const sf::Texture& tex);

            void handleEvent    (sf::Event e, const sf::RenderWindow& window) override;
            void render         (sf::RenderTarget& renderer) override;
            void setPosition    (const sf::Vector2f& pos)   override;
            sf::Vector2f getSize() const    override;

        private:
            void updateText();

            sf::Vector2f    m_position;

            Rectangle   m_button;
            Text        m_text;
            std::function<void(void)> m_function = [](){};

    };

    inline std::unique_ptr<Button> makeButton() { return std::make_unique<Button>(); }
}

#include <functional>


namespace gui
{
    class TextBox : public gui::Widget
    {
        public:
            TextBox(std::string& modString);

            void setLabel       (const std::string& str);
            void setTexture     (const sf::Texture& tex);

            void handleEvent    (sf::Event e, const sf::RenderWindow& window) override;
            void render         (sf::RenderTarget& renderer)    override;
            void setPosition    (const sf::Vector2f& pos)       override;
            sf::Vector2f getSize() const                        override;

        private:
            void handleClick    (sf::Event e, const sf::RenderWindow& window);
            void handleTextInput(sf::Event e);

            bool isValidCharacter   (unsigned char keyCode);
            bool isBackspace        (unsigned char keycode);

            sf::Vector2f    m_position;

            Rectangle       m_rect;
            Text            m_text;
            Text            m_label;
            std::string*    m_pModString;

            bool m_isActive = false;
    };

    inline std::unique_ptr<TextBox> makeTextBox(std::string& modStr) { return std::make_unique<TextBox>(modStr); }
}

#include <SFML/Graphics.hpp>


class Game;

class StateBase : public NonCopyable
{
    public:
        StateBase(Game& game, const char* name)
            : m_pGame(&game)
            , m_name(name)
        {}

        virtual ~StateBase() = default;

        virtual void handleEvent(sf::Event e) {}
        virtual void handleInput() = 0;
        virtual void update(sf::Time deltaTime) {}
        virtual void fixedUpdate(sf::Time deltaTime) {}
        virtual void render(sf::RenderTarget& renderer) = 0;

        const std::string& getName() { return m_name;  }

    protected:
        Game* m_pGame;
        std::string m_name;
};

#include <SFML/Graphics.hpp>

namespace SpaceInvaders
{
    /*
        Class to represent a single invader
    */
    class Invader : public Collidable
    {
    public:
        enum class Type
        {
            Octopus, Crab, Squid,
        };

        Invader(const sf::Vector2f& initialLocation, Type type);

        void move(float x, float y);

        const sf::Vector2f& getPosition() const;
        bool isAlive() const;
        Type getType() const;

        void onCollide(Collidable& other) override;

        void makeAlive()
        {
            m_isAlive = true;
            m_location = m_initialPosition;
        }

    private:
        const sf::Vector2f m_initialPosition;
        sf::Vector2f m_location;
        bool m_isAlive = false;
        Type m_type;

    public:
        constexpr static float WIDTH = 48;
        constexpr static float HEIGHT = 32;
    };
}

#include <SFML/Graphics.hpp>


namespace SpaceInvaders
{
    class Projectile : public Collidable
    {
    public:
        constexpr static float HEIGHT = 24;
        constexpr static float WIDTH = 12;

        enum class Type
        {
            Rectangle,
            Lightning,
            Knife
        };

        enum class Direction
        {
            Up = -1,
            Down = 1
        };

        Projectile(const sf::Vector2f& position, Type type, Direction direction);
        void update(float dt);
        void onCollide(Collidable& other) override;
        void destroy();

        const sf::Vector2f& getPosition() const;
        Type getType() const;
        bool isActive() const;
        Direction getDirection() const;

        int getID() const;

    private:
        sf::Vector2f m_position;
        Type m_type;
        Direction m_direction;
        bool m_isActive = true;
        int m_id;
    };
}

#include <SFML/Graphics.hpp>
#include <array>


namespace SpaceInvaders
{
    class Projectile;

    class Shield : private Collidable
    {
        constexpr static int SECT_SIZE = 20;

        enum class SectorStyle
        {
            Square, SlopeUp, SlopeDown, SlopeUnderUp, SlopeUnderDown
        };
        class ShieldSection : public Collidable
        {
        public:
            ShieldSection(float tlX, float tlY, SectorStyle style);

            void draw(sf::RenderTarget& target);

            const sf::Vector2f& getPosition() const;
            void onCollide(Collidable& other) {}

            sf::Vector2f isTouching(const Projectile& other);

            void destroyArea(int x, int y);

        private:
            void calculatePixelCoord(int x, int y, sf::Vertex& v, SectorStyle style);
            std::array<sf::Vertex, SECT_SIZE * SECT_SIZE> m_pixels;
            sf::Vector2f m_position;
        };

    public:
        constexpr static int SIZE = SECT_SIZE * 4;

        Shield(float x);

        void draw(sf::RenderTarget& target);
        bool isTouching(const Projectile& projectile);

        const sf::Vector2f& getPosition() const;
        void onCollide(Collidable& other) {}

    private:
        ShieldSection & getSection(int x, int y);

        void destroyPoint(float relX, float relY);

        std::vector<ShieldSection> m_sections;
        sf::Vector2f m_position;
    };
}

#include <SFML/Graphics.hpp>

namespace SpaceInvaders
{

    class StarryBackground
    {
    public:
        StarryBackground();

        void update(float dt);

        void draw(sf::RenderTarget& renderer);

    private:
        void giveStarRandomStartLocation(sf::Vertex& v);

        std::vector<sf::Vertex> m_stars;

        Random<> m_rng;
    };
}

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>


namespace gui
{

class StackMenu : public NonCopyable
{
    public:
        StackMenu(const sf::RenderWindow& window, float baseY);
        StackMenu(const sf::Vector2f& position);

        StackMenu(StackMenu&& other);
        StackMenu& operator =(StackMenu&& other);

        ~StackMenu() = default;

        void addWidget(std::unique_ptr<Widget> w);
        /*
        template<typename T, typename... Args>
        void addWidget(Args&&... args) {
            auto w = std::make_unique<T>(std::forward<Args>(args)...);
            initWidget(*w);
            m_widgets.push_back(std::move(w));
        }*/

        void setTitle(const std::string& title);

        void handleEvent   (sf::Event e, const sf::RenderWindow& window);
        void render        (sf::RenderTarget& renderer);

    private:
        void initWidget(Widget& w);

        std::vector<std::unique_ptr<Widget>> m_widgets;
        sf::RectangleShape m_background;

        sf::Vector2f m_basePosition;
        sf::Vector2f m_baseSize;

        Widget::Text m_titleText;
};

}

#include <SFML/Graphics.hpp>

#include <SFML/Audio.hpp>


namespace SpaceInvaders
{
    /**
        Represents the player
    */
    class Player : public Collidable
    {
    public:
        constexpr static int WIDTH = 44;
        constexpr static int HEIGHT = 32;

        Player();

        void input();
        void update(float dt);
        void draw(sf::RenderTarget& target);

        //Gets the coordinates of the gun
        sf::Vector2f getGunPosition() const;

        const sf::Vector2f& getPosition() const;
        void onCollide(Collidable& other) override;

        int getLives() const;
        bool isAlive() const;

        void tryRevive();

    private:
        void restart();

        sf::RectangleShape m_sprite;
        Animation m_deathAnimation;
        sf::Vector2f m_velocity;
        sf::Clock m_deathTimer;

        bool m_isAlive = true;
        int m_livesLeft = 3;

        sf::Sound m_deathSound;
    };
}

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>



/**
    Main controlling class of the game.
    Handles state switches and the main loop, as well
    as counting the FPS
*/
class Game : public NonCopyable, public NonMovable
{
    public:
        Game();

        void run();

        template<typename T, typename... Args>
        void pushState(Args&&... args);
        void pushState(std::unique_ptr<StateBase> state);
        void popState();
        void exitGame();
        template<typename T, typename... Args>
        void changeState(Args&&... args);

        const sf::RenderWindow& getWindow() const;

    private:
        void handleEvent();
        void tryPop();

        StateBase& getCurrentState();

        sf::RenderWindow m_window;
        std::vector<std::unique_ptr<StateBase>> m_states;

        FPSCounter counter;

        bool m_shouldPop = false;
        bool m_shouldExit = false;
        bool m_shouldChageState = false;
        std::unique_ptr<StateBase> m_change;

};

template<typename T, typename... Args>
inline void Game::pushState(Args&&... args)
{
    pushState(std::make_unique<T>(std::forward<Args>(args)...));
}

template<typename T, typename ...Args>
inline void Game::changeState(Args && ...args)
{
    m_change = std::make_unique<T>(std::forward<Args>(args)...);
    m_shouldPop = true;
    m_shouldChageState = true;
}

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace SpaceInvaders
{
    class UFO : public Collidable
    {
    public:
        enum class State
        {
            Waiting,
            Flying,
            Destroyed
        };

        UFO(Random<>& rand);

        State getState() const;

        void update(float dt);

        void draw(sf::RenderTarget& window);

        const sf::Vector2f& getPosition() const;
        void onCollide(Collidable& other);

    private:
        Random<>& m_rng;

        sf::RectangleShape m_sprite;
        float m_vx;
        State m_state;
        Animation m_animation;

        sf::Sound m_flyingSound;
    };
}


#include <vector>
#include <SFML/Audio.hpp>


namespace SpaceInvaders 
{
    class World;

    using CollisionResult = std::pair<int, std::vector<sf::Vector2f>>;

    /**
        Class to manage the drawing and updating of invaders
    */
    class InvaderManager
    {
    public:
        InvaderManager(World& world);

        //Moves all of the invaders to the left or right, if the clock has reached a certain time
        void tryStepInvaders();

        //Draws all of the alive invaders
        void drawInvaders(sf::RenderTarget& target);

        //Tries to collide the invaders with the projectiles
        //Returns the points of collision
        CollisionResult tryCollideWithProjectiles(std::vector<Projectile>& projectiles);

        //This is for firing projectiles from the enemy
        sf::Vector2f getRandomLowestInvaderPoint(Random<>& random);

        int getAliveInvadersCount() const;

        /*
            These two functions are for the initilization of the invaders.
            It will add one invader at a time unil all have been added.
        */
        void initAddInvader();
        bool areInvadersAlive() const;

    private:
        //Changes time between the alien's steps based on number alive
        void updateStepDelay();

        //Checks the invaders position to see if all the aliens should move down
        //Or if the game is over
        bool testInvaderPosition(const Invader& invader) const;

        std::vector<Invader> m_invaders;
        sf::Clock m_stepTimer;
        sf::Time m_stepGap;

        World& m_world;


        AnimationRenderer m_invaderRenderer;
        unsigned m_aliveInvaders;

        bool m_hasAllInvadersBeenAdded = false;

        bool m_isMovingLeft = false;
        bool m_moveDown = false;

        int m_initX = 0;
        int m_initY = 4;
        int m_ticks = 0;

        sf::Sound m_stepSounds[4];
        sf::Sound m_invaderKilledSound;
    };
}

#include <SFML/Graphics.hpp>


namespace SpaceInvaders
{
    /**
        The class which manages the world and th interactions between different entites
    */
    class World
    {
    public:
        World();

        void input();
        int update(float dt);
        void draw(sf::RenderTarget& target);

        const Player& getPlayer() const;

        bool isGameOver() const;

        void setGameIsOver() { m_isGameOver = true; }

    private:
        void playerProjectileInput();
        void enemyProjectileFire();
        CollisionResult getCollisionResult(float dtt);
        void updateProjectiles(float dt, std::vector<sf::Vector2f>& collisionPoints);

        AnimationRenderer m_projectileRenderer;
        InvaderManager m_invaders;
        Player m_player;
        UFO m_ufo;

        std::vector<Projectile> m_projectiles;
        std::vector<Explosion> m_explosions;
        std::vector<Shield> m_shields;

        sf::RectangleShape m_explodeShape;
        sf::Clock m_invaderShotClock;
        sf::Clock m_playerShotClock;
        sf::Clock m_animTimer;

        sf::Sound m_playerShoot;

        Random<> m_rng;

        bool m_isGameOver = false;
    };
}



namespace SpaceInvaders
{
    /*
        The main state; where all the gameplay happens
    */
    class StatePlaying : public StateBase
    {
    public:
        StatePlaying(Game& game);

        void handleEvent(sf::Event e)                   override;
        void handleInput()                              override;
        void update(sf::Time deltaTime)            override;
        void render(sf::RenderTarget& renderer)    override;

    private:
        World m_world;

        int m_score = 0;
        bool m_isGameover;
        sf::Clock m_gameOverClock;

        gui::StackMenu m_gameOverMenu;

        //Displays how many lives the player has left
        class LifeDisplay
        {
        public:
            LifeDisplay();

            void draw(sf::RenderTarget& window, int lives);

        private:
            gui::Widget::Text m_label;
            sf::RectangleShape m_lifeStamp;
        } m_lifeDisplay;

        //Displays the Player's current score
        class ScoreDisplay
        {
        public:
            ScoreDisplay(float centreX, const std::string& text);

            void update(int newScore);

            void draw(sf::RenderTarget& target);

            int getCurrentScoreDisplayed() const;
        private:
            void updateDisplay();

            gui::Widget::Text m_label;
            std::string m_text;
            int m_currentScore;
            float m_centerPosition;
        } m_scoreDisplay, m_highestScoreDisplay;
    };
}

namespace SpaceInvaders
{
    class StateHighscores : public StateBase
    {
        using Entry = std::pair<std::string, int>;

        struct EntryBox
        {
        public:
            EntryBox(int position, const std::string& name, int score);

            void draw(sf::RenderTarget& renderer);

        private:
            sf::RectangleShape m_background;
            gui::Widget::Text m_nameText;
            gui::Widget::Text m_scoreText;

        };

        enum class State {
            Submitting,
            Viewing
        };

    public:
        StateHighscores(Game& game, int score);
        StateHighscores(Game& game);

        void handleEvent(sf::Event e)   override;
        void handleInput() override {};
        void update(sf::Time deltaTime) override;
        void render(sf::RenderTarget& renderer) override;

        static int getHighestScore();

    private:
        void initViewMenu();
        void initSubmitMenu();

        void switchToViewMenu();
        void createHighscoreView();
        void loadScores();
        void writeScores();
        void sortScores();
        void submitScore();

        gui::StackMenu m_submitScoreMenu;
        gui::StackMenu m_highscoreMenu;
        gui::StackMenu* m_pActiveMenu;

        std::vector<Entry> m_scores;
        std::vector<EntryBox> m_entryBoxes;

        StarryBackground m_background;

        State m_state;

        std::string m_submitString;
        int m_scoreToSubmit = 0;

        sf::RectangleShape m_banner;
    };
}


namespace SpaceInvaders
{
    class StateMainMenu : public StateBase
    {
    public:
        StateMainMenu(Game& game);

        void handleEvent(sf::Event e)   override;
        void handleInput() override {};
        void update(sf::Time deltaTime) override;
        void render(sf::RenderTarget& renderer) override;

    private:
        gui::StackMenu m_mainMenu;
        sf::RectangleShape m_banner;

        StarryBackground m_background;
    };
}
//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by SpaceInvaders.rc
//
#define IDI_ICON1                       102

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        103
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1001
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif

#include <unordered_map>
#include <string>

/**
    Holds all the resources of the game
*/
template<typename Resource>
class ResourceManager
{
    public:
        ResourceManager (const std::string& folder, const std::string& extention)
        :   m_folder    ("res/" + folder + "/")
        ,   m_extention ("." + extention)
        { }

        const Resource& get(const std::string& name)
        {
            if (!exists(name)) {
                add(name);
            }

            return m_resources.at(name);
        }

        bool exists(const std::string& name) const
        {
            return m_resources.find(name) != m_resources.end();
        }

        void add(const std::string& name)
        {
            Resource r;

            //if the resource fails to load, then it adds a default "fail" resource
            if(!r.loadFromFile(getFullFilename(name))) {
                Resource fail;
                fail.loadFromFile(m_folder + "_fail_" + m_extention);
                m_resources.insert(std::make_pair(name, fail));
            }
            else {
                m_resources.insert(std::make_pair(name, r));
            }
        }

    private:
        std::string getFullFilename(const std::string& name)
        {
            return m_folder + name + m_extention;
        }

        const std::string m_folder;
        const std::string m_extention;

        std::unordered_map<std::string, Resource> m_resources;
};

#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
    public:
        struct Frame
        {
            Frame(const sf::IntRect& bnds, sf::Time dly)
            :   bounds  (bnds)
            ,   delay   (dly) {}

            sf::IntRect bounds; //The area in a texture of the frame
            sf::Time    delay;  //Time delay to next frame
        };

        Animation(unsigned frameWidth, unsigned frameHeight);

        void addFrame(unsigned index, sf::Time delay);

        const sf::IntRect& getFrame();

    private:
        sf::Clock m_timer;              //Timer for progressing the animation

        std::vector<Frame> m_frames;    //List of animation frames

        unsigned m_framePointer = 0;    //The index of the current active frame
        const unsigned FRAME_WIDTH; 
        const unsigned FRAME_HEIGHT;      

};

#include <string>

std::string getFileContent(const std::string& filePath, bool throws);

#include <SFML/Graphics.hpp>

class FPSCounter
{
    public:
        FPSCounter();

        void update();

        void draw(sf::RenderTarget& renderer);

    private:
        sf::Text m_text;
        sf::Font m_font;

        sf::Clock m_delayTimer;
        sf::Clock m_fpsTimer;

        float m_fps = 0;

        int m_frameCount = 0;
};

constexpr float PI = 3.14159265f;
constexpr float MIN_PI = 3.14f;

template <typename T>
T toRadians(T degrees)
{
    return degrees * PI / 180;
}

template <typename T>
T toDegrees(T radians)
{
    return (radians * 180) / PI;
}

struct NonCopyable
{
    NonCopyable() = default;
    NonCopyable& operator = (const NonCopyable&) = delete;
    NonCopyable(const NonCopyable&) = delete;
};


struct NonMovable
{
    NonMovable() = default;
    NonMovable& operator = (NonCopyable&&) = delete;
    NonMovable(NonCopyable&&) = delete;
};

#include <random>
#include <ctime>

template <typename Engine = std::mt19937>
class Random
{
    template<typename T>
    using UniformDist = std::uniform_real_distribution<T>;
    using UniformIntDist = std::uniform_int_distribution<int>;

    public:
        static Random gRand;

        Random(int seed = std::time(nullptr))
        :   m_prng  (seed)
        { }

        int getIntInRange(int low, int high)
        {
            return getNumberInRange<UniformIntDist>(low, high);
        }

        float getFloatInRange(float low, float high)
        {
            return getNumberInRange<UniformDist<float>>(low, high);
        }

        template<typename T>
        T getNumberInRange(T low, T high)
        {
            return getNumberInRange<UniformDist<T>>(low, high);
        }

        template<typename Dist, typename T>
        T getNumberInRange(T low, T high)
        {
            Dist dist(low, high);
            return dist(m_prng);
        }

    private:
        Engine m_prng;
};

#include <SFML/Graphics.hpp>

class ToggleKey
{
    public:
        ToggleKey(sf::Keyboard::Key);

        bool isKeyPressed();

    private:
        sf::Keyboard::Key m_key;
        sf::Clock m_delayTimer;
};

#include <SFML/Graphics.hpp>

namespace SpaceInvaders
{
    /*
        Utility class for rendering a large number of entites which share
        the same animation
    */
    class AnimationRenderer
    {
    public:
        AnimationRenderer(int frameWidth, int frameHeight,
            float entityWidth, float entityHeight,
            const sf::Texture& spriteSheet);

        //Changes to the next frame
        void nextFrame();

        //Renders a single entity, using the current animation frame
        void renderEntity(sf::RenderTarget& renderer, int type, const sf::Vector2f& position);

    private:
        sf::RectangleShape m_entity;
        int m_currentFrame;
        const int m_frameWidth;
        const int m_frameHeight;
    };
}

#include <SFML/Graphics.hpp>

namespace SpaceInvaders
{
    class Collidable
    {
    public:
        Collidable(float width, float height);

        bool tryCollideWith(Collidable& other);
        sf::FloatRect getBox() const;

        virtual const sf::Vector2f& getPosition() const = 0;
        virtual void onCollide(Collidable& other) = 0;

    private:
        sf::Vector2f m_size;
    };
}

namespace Display 
{
    constexpr unsigned WIDTH = 1000;
    constexpr unsigned HEIGHT = 800;
}

#include <SFML/Graphics.hpp>

namespace SpaceInvaders
{
    /*
        Represents a single explosion entity
    */
    class Explosion
    {
    public:
        Explosion(const sf::Vector2f& position);

        bool isLifeOver() const;
        const sf::Vector2f& getPosition() const;

    private:
        sf::Vector2f m_position;        //The position of the explosion
        sf::Clock m_lifetimeCounter;    //Clock for checking if the explosion is outlived
    };
}

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class ResourceHolder : public NonCopyable, public NonMovable
{
    public:
        static ResourceHolder& get();

        ResourceManager<sf::Font>           fonts;
        ResourceManager<sf::Texture>        textures;
        ResourceManager<sf::SoundBuffer>    soundBuffers;

    private:
        ResourceHolder();
};

#include <SFML/Graphics.hpp>
#include <memory>

namespace gui
{
    class Widget
    {
        public:
            virtual void handleEvent(sf::Event e, const sf::RenderWindow& window) = 0;

            virtual void render(sf::RenderTarget& renderer) = 0;

            virtual void setPosition(const sf::Vector2f& pos) = 0;

            virtual sf::Vector2f getSize() const = 0;

            class Text : public sf::Text
            {
                public:
                    Text();
            };

            class Rectangle : public sf::RectangleShape
            {
                public:
                    bool isRolledOn (const sf::RenderWindow& window) const;
                    bool isClicked  (sf::Event, const sf::RenderWindow& window);
            };
    };
}


#include <functional>


namespace gui
{
    enum class ButtonSize
    {
        Small,
        Wide,
    };

    class Button : public gui::Widget
    {
        public:
            Button(ButtonSize s = ButtonSize::Wide);

            void setFunction(std::function<void(void)> func);
            void setText    (const std::string& str);
            void setTexture (const sf::Texture& tex);

            void handleEvent    (sf::Event e, const sf::RenderWindow& window) override;
            void render         (sf::RenderTarget& renderer) override;
            void setPosition    (const sf::Vector2f& pos)   override;
            sf::Vector2f getSize() const    override;

        private:
            void updateText();

            sf::Vector2f    m_position;

            Rectangle   m_button;
            Text        m_text;
            std::function<void(void)> m_function = [](){};

    };

    inline std::unique_ptr<Button> makeButton() { return std::make_unique<Button>(); }
}

#include <functional>


namespace gui
{
    class TextBox : public gui::Widget
    {
        public:
            TextBox(std::string& modString);

            void setLabel       (const std::string& str);
            void setTexture     (const sf::Texture& tex);

            void handleEvent    (sf::Event e, const sf::RenderWindow& window) override;
            void render         (sf::RenderTarget& renderer)    override;
            void setPosition    (const sf::Vector2f& pos)       override;
            sf::Vector2f getSize() const                        override;

        private:
            void handleClick    (sf::Event e, const sf::RenderWindow& window);
            void handleTextInput(sf::Event e);

            bool isValidCharacter   (unsigned char keyCode);
            bool isBackspace        (unsigned char keycode);

            sf::Vector2f    m_position;

            Rectangle       m_rect;
            Text            m_text;
            Text            m_label;
            std::string*    m_pModString;

            bool m_isActive = false;
    };

    inline std::unique_ptr<TextBox> makeTextBox(std::string& modStr) { return std::make_unique<TextBox>(modStr); }
}

#include <SFML/Graphics.hpp>


class Game;

class StateBase : public NonCopyable
{
    public:
        StateBase(Game& game, const char* name)
            : m_pGame(&game)
            , m_name(name)
        {}

        virtual ~StateBase() = default;

        virtual void handleEvent(sf::Event e) {}
        virtual void handleInput() = 0;
        virtual void update(sf::Time deltaTime) {}
        virtual void fixedUpdate(sf::Time deltaTime) {}
        virtual void render(sf::RenderTarget& renderer) = 0;

        const std::string& getName() { return m_name;  }

    protected:
        Game* m_pGame;
        std::string m_name;
};

#include <SFML/Graphics.hpp>

namespace SpaceInvaders
{
    /*
        Class to represent a single invader
    */
    class Invader : public Collidable
    {
    public:
        enum class Type
        {
            Octopus, Crab, Squid,
        };

        Invader(const sf::Vector2f& initialLocation, Type type);

        void move(float x, float y);

        const sf::Vector2f& getPosition() const;
        bool isAlive() const;
        Type getType() const;

        void onCollide(Collidable& other) override;

        void makeAlive()
        {
            m_isAlive = true;
            m_location = m_initialPosition;
        }

    private:
        const sf::Vector2f m_initialPosition;
        sf::Vector2f m_location;
        bool m_isAlive = false;
        Type m_type;

    public:
        constexpr static float WIDTH = 48;
        constexpr static float HEIGHT = 32;
    };
}

#include <SFML/Graphics.hpp>


namespace SpaceInvaders
{
    class Projectile : public Collidable
    {
    public:
        constexpr static float HEIGHT = 24;
        constexpr static float WIDTH = 12;

        enum class Type
        {
            Rectangle,
            Lightning,
            Knife
        };

        enum class Direction
        {
            Up = -1,
            Down = 1
        };

        Projectile(const sf::Vector2f& position, Type type, Direction direction);
        void update(float dt);
        void onCollide(Collidable& other) override;
        void destroy();

        const sf::Vector2f& getPosition() const;
        Type getType() const;
        bool isActive() const;
        Direction getDirection() const;

        int getID() const;

    private:
        sf::Vector2f m_position;
        Type m_type;
        Direction m_direction;
        bool m_isActive = true;
        int m_id;
    };
}

#include <SFML/Graphics.hpp>
#include <array>


namespace SpaceInvaders
{
    class Projectile;

    class Shield : private Collidable
    {
        constexpr static int SECT_SIZE = 20;

        enum class SectorStyle
        {
            Square, SlopeUp, SlopeDown, SlopeUnderUp, SlopeUnderDown
        };
        class ShieldSection : public Collidable
        {
        public:
            ShieldSection(float tlX, float tlY, SectorStyle style);

            void draw(sf::RenderTarget& target);

            const sf::Vector2f& getPosition() const;
            void onCollide(Collidable& other) {}

            sf::Vector2f isTouching(const Projectile& other);

            void destroyArea(int x, int y);

        private:
            void calculatePixelCoord(int x, int y, sf::Vertex& v, SectorStyle style);
            std::array<sf::Vertex, SECT_SIZE * SECT_SIZE> m_pixels;
            sf::Vector2f m_position;
        };

    public:
        constexpr static int SIZE = SECT_SIZE * 4;

        Shield(float x);

        void draw(sf::RenderTarget& target);
        bool isTouching(const Projectile& projectile);

        const sf::Vector2f& getPosition() const;
        void onCollide(Collidable& other) {}

    private:
        ShieldSection & getSection(int x, int y);

        void destroyPoint(float relX, float relY);

        std::vector<ShieldSection> m_sections;
        sf::Vector2f m_position;
    };
}

#include <SFML/Graphics.hpp>

namespace SpaceInvaders
{

    class StarryBackground
    {
    public:
        StarryBackground();

        void update(float dt);

        void draw(sf::RenderTarget& renderer);

    private:
        void giveStarRandomStartLocation(sf::Vertex& v);

        std::vector<sf::Vertex> m_stars;

        Random<> m_rng;
    };
}

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>


namespace gui
{

class StackMenu : public NonCopyable
{
    public:
        StackMenu(const sf::RenderWindow& window, float baseY);
        StackMenu(const sf::Vector2f& position);

        StackMenu(StackMenu&& other);
        StackMenu& operator =(StackMenu&& other);

        ~StackMenu() = default;

        void addWidget(std::unique_ptr<Widget> w);
        /*
        template<typename T, typename... Args>
        void addWidget(Args&&... args) {
            auto w = std::make_unique<T>(std::forward<Args>(args)...);
            initWidget(*w);
            m_widgets.push_back(std::move(w));
        }*/

        void setTitle(const std::string& title);

        void handleEvent   (sf::Event e, const sf::RenderWindow& window);
        void render        (sf::RenderTarget& renderer);

    private:
        void initWidget(Widget& w);

        std::vector<std::unique_ptr<Widget>> m_widgets;
        sf::RectangleShape m_background;

        sf::Vector2f m_basePosition;
        sf::Vector2f m_baseSize;

        Widget::Text m_titleText;
};

}

#include <SFML/Graphics.hpp>

#include <SFML/Audio.hpp>


namespace SpaceInvaders
{
    /**
        Represents the player
    */
    class Player : public Collidable
    {
    public:
        constexpr static int WIDTH = 44;
        constexpr static int HEIGHT = 32;

        Player();

        void input();
        void update(float dt);
        void draw(sf::RenderTarget& target);

        //Gets the coordinates of the gun
        sf::Vector2f getGunPosition() const;

        const sf::Vector2f& getPosition() const;
        void onCollide(Collidable& other) override;

        int getLives() const;
        bool isAlive() const;

        void tryRevive();

    private:
        void restart();

        sf::RectangleShape m_sprite;
        Animation m_deathAnimation;
        sf::Vector2f m_velocity;
        sf::Clock m_deathTimer;

        bool m_isAlive = true;
        int m_livesLeft = 3;

        sf::Sound m_deathSound;
    };
}

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>



/**
    Main controlling class of the game.
    Handles state switches and the main loop, as well
    as counting the FPS
*/
class Game : public NonCopyable, public NonMovable
{
    public:
        Game();

        void run();

        template<typename T, typename... Args>
        void pushState(Args&&... args);
        void pushState(std::unique_ptr<StateBase> state);
        void popState();
        void exitGame();
        template<typename T, typename... Args>
        void changeState(Args&&... args);

        const sf::RenderWindow& getWindow() const;

    private:
        void handleEvent();
        void tryPop();

        StateBase& getCurrentState();

        sf::RenderWindow m_window;
        std::vector<std::unique_ptr<StateBase>> m_states;

        FPSCounter counter;

        bool m_shouldPop = false;
        bool m_shouldExit = false;
        bool m_shouldChageState = false;
        std::unique_ptr<StateBase> m_change;

};

template<typename T, typename... Args>
inline void Game::pushState(Args&&... args)
{
    pushState(std::make_unique<T>(std::forward<Args>(args)...));
}

template<typename T, typename ...Args>
inline void Game::changeState(Args && ...args)
{
    m_change = std::make_unique<T>(std::forward<Args>(args)...);
    m_shouldPop = true;
    m_shouldChageState = true;
}

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace SpaceInvaders
{
    class UFO : public Collidable
    {
    public:
        enum class State
        {
            Waiting,
            Flying,
            Destroyed
        };

        UFO(Random<>& rand);

        State getState() const;

        void update(float dt);

        void draw(sf::RenderTarget& window);

        const sf::Vector2f& getPosition() const;
        void onCollide(Collidable& other);

    private:
        Random<>& m_rng;

        sf::RectangleShape m_sprite;
        float m_vx;
        State m_state;
        Animation m_animation;

        sf::Sound m_flyingSound;
    };
}


#include <vector>
#include <SFML/Audio.hpp>


namespace SpaceInvaders 
{
    class World;

    using CollisionResult = std::pair<int, std::vector<sf::Vector2f>>;

    /**
        Class to manage the drawing and updating of invaders
    */
    class InvaderManager
    {
    public:
        InvaderManager(World& world);

        //Moves all of the invaders to the left or right, if the clock has reached a certain time
        void tryStepInvaders();

        //Draws all of the alive invaders
        void drawInvaders(sf::RenderTarget& target);

        //Tries to collide the invaders with the projectiles
        //Returns the points of collision
        CollisionResult tryCollideWithProjectiles(std::vector<Projectile>& projectiles);

        //This is for firing projectiles from the enemy
        sf::Vector2f getRandomLowestInvaderPoint(Random<>& random);

        int getAliveInvadersCount() const;

        /*
            These two functions are for the initilization of the invaders.
            It will add one invader at a time unil all have been added.
        */
        void initAddInvader();
        bool areInvadersAlive() const;

    private:
        //Changes time between the alien's steps based on number alive
        void updateStepDelay();

        //Checks the invaders position to see if all the aliens should move down
        //Or if the game is over
        bool testInvaderPosition(const Invader& invader) const;

        std::vector<Invader> m_invaders;
        sf::Clock m_stepTimer;
        sf::Time m_stepGap;

        World& m_world;


        AnimationRenderer m_invaderRenderer;
        unsigned m_aliveInvaders;

        bool m_hasAllInvadersBeenAdded = false;

        bool m_isMovingLeft = false;
        bool m_moveDown = false;

        int m_initX = 0;
        int m_initY = 4;
        int m_ticks = 0;

        sf::Sound m_stepSounds[4];
        sf::Sound m_invaderKilledSound;
    };
}

#include <SFML/Graphics.hpp>


namespace SpaceInvaders
{
    /**
        The class which manages the world and th interactions between different entites
    */
    class World
    {
    public:
        World();

        void input();
        int update(float dt);
        void draw(sf::RenderTarget& target);

        const Player& getPlayer() const;

        bool isGameOver() const;

        void setGameIsOver() { m_isGameOver = true; }

    private:
        void playerProjectileInput();
        void enemyProjectileFire();
        CollisionResult getCollisionResult(float dtt);
        void updateProjectiles(float dt, std::vector<sf::Vector2f>& collisionPoints);

        AnimationRenderer m_projectileRenderer;
        InvaderManager m_invaders;
        Player m_player;
        UFO m_ufo;

        std::vector<Projectile> m_projectiles;
        std::vector<Explosion> m_explosions;
        std::vector<Shield> m_shields;

        sf::RectangleShape m_explodeShape;
        sf::Clock m_invaderShotClock;
        sf::Clock m_playerShotClock;
        sf::Clock m_animTimer;

        sf::Sound m_playerShoot;

        Random<> m_rng;

        bool m_isGameOver = false;
    };
}



namespace SpaceInvaders
{
    /*
        The main state; where all the gameplay happens
    */
    class StatePlaying : public StateBase
    {
    public:
        StatePlaying(Game& game);

        void handleEvent(sf::Event e)                   override;
        void handleInput()                              override;
        void update(sf::Time deltaTime)            override;
        void render(sf::RenderTarget& renderer)    override;

    private:
        World m_world;

        int m_score = 0;
        bool m_isGameover;
        sf::Clock m_gameOverClock;

        gui::StackMenu m_gameOverMenu;

        //Displays how many lives the player has left
        class LifeDisplay
        {
        public:
            LifeDisplay();

            void draw(sf::RenderTarget& window, int lives);

        private:
            gui::Widget::Text m_label;
            sf::RectangleShape m_lifeStamp;
        } m_lifeDisplay;

        //Displays the Player's current score
        class ScoreDisplay
        {
        public:
            ScoreDisplay(float centreX, const std::string& text);

            void update(int newScore);

            void draw(sf::RenderTarget& target);

            int getCurrentScoreDisplayed() const;
        private:
            void updateDisplay();

            gui::Widget::Text m_label;
            std::string m_text;
            int m_currentScore;
            float m_centerPosition;
        } m_scoreDisplay, m_highestScoreDisplay;
    };
}

namespace SpaceInvaders
{
    class StateHighscores : public StateBase
    {
        using Entry = std::pair<std::string, int>;

        struct EntryBox
        {
        public:
            EntryBox(int position, const std::string& name, int score);

            void draw(sf::RenderTarget& renderer);

        private:
            sf::RectangleShape m_background;
            gui::Widget::Text m_nameText;
            gui::Widget::Text m_scoreText;

        };

        enum class State {
            Submitting,
            Viewing
        };

    public:
        StateHighscores(Game& game, int score);
        StateHighscores(Game& game);

        void handleEvent(sf::Event e)   override;
        void handleInput() override {};
        void update(sf::Time deltaTime) override;
        void render(sf::RenderTarget& renderer) override;

        static int getHighestScore();

    private:
        void initViewMenu();
        void initSubmitMenu();

        void switchToViewMenu();
        void createHighscoreView();
        void loadScores();
        void writeScores();
        void sortScores();
        void submitScore();

        gui::StackMenu m_submitScoreMenu;
        gui::StackMenu m_highscoreMenu;
        gui::StackMenu* m_pActiveMenu;

        std::vector<Entry> m_scores;
        std::vector<EntryBox> m_entryBoxes;

        StarryBackground m_background;

        State m_state;

        std::string m_submitString;
        int m_scoreToSubmit = 0;

        sf::RectangleShape m_banner;
    };
}


namespace SpaceInvaders
{
    class StateMainMenu : public StateBase
    {
    public:
        StateMainMenu(Game& game);

        void handleEvent(sf::Event e)   override;
        void handleInput() override {};
        void update(sf::Time deltaTime) override;
        void render(sf::RenderTarget& renderer) override;

    private:
        gui::StackMenu m_mainMenu;
        sf::RectangleShape m_banner;

        StarryBackground m_background;
    };
}


#include <iostream>

Game::Game()
:   m_window    ({ Display::WIDTH, Display::HEIGHT}, "Space Invaders")
{
    m_window.setPosition({m_window.getPosition().x, 0});
    m_window.setFramerateLimit(60);
    pushState<SpaceInvaders::StateMainMenu>(*this);

    sf::Image icon;
    icon.loadFromFile("res/txrs/icon.png");
    m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

//Runs the main loop
void Game::run()
{
    constexpr unsigned TPS = 30; //ticks per seconds
    const sf::Time     timePerUpdate = sf::seconds(1.0f / float(TPS));
    unsigned ticks = 0;

    sf::Clock timer;
    auto lastTime = sf::Time::Zero;
    auto lag      = sf::Time::Zero;

    //Main loop of the game
    while (m_window.isOpen() && !m_states.empty()) {
        auto& state = getCurrentState();

        //Get times
        auto time = timer.getElapsedTime();
        auto elapsed = time - lastTime;
        lastTime = time;
        lag += elapsed;

        //Real time update
        state.handleInput();
        state.update(elapsed);
        counter.update();

        //Fixed time update
        while (lag >= timePerUpdate)
        {
            ticks++;
            lag -= timePerUpdate;
            state.fixedUpdate(elapsed);
        }

        //Render
        m_window.clear();
        state.render(m_window);
        counter.draw(m_window);
        m_window.display();


        //Handle window events
        handleEvent();
        tryPop();
    }
}

//Tries to pop the current game state
void Game::tryPop()
{
    if (m_shouldPop) {
        m_shouldPop = false;
        if (m_shouldExit) {
            m_states.clear();
            return;
        }
        else if (m_shouldChageState) {
            m_shouldChageState = false;
            m_states.pop_back();
            pushState(std::move(m_change));
            return;
        }
        
        m_states.pop_back();
    }
}

//Handles window events, called every frame
void Game::handleEvent()
{
    sf::Event e;

    while (m_window.pollEvent(e)) {
        getCurrentState().handleEvent(e);
        switch (e.type) {
            case sf::Event::Closed:
                m_window.close();
                break;

            default:
                break;

        }
    }
}

//Returns a reference to the current game state
StateBase& Game::getCurrentState()
{
    return *m_states.back();
}

void Game::pushState(std::unique_ptr<StateBase> state)
{
    m_states.push_back(std::move(state));
}

//Flags a boolean for the game to pop state
void Game::popState()
{
    m_shouldPop = true;
}

void Game::exitGame()
{
    m_shouldPop = true;
    m_shouldExit = true;
}


//on tin
const sf::RenderWindow& Game::getWindow() const
{
    return m_window;
}

int main()
{
    Game game;
    game.run();
}

#include <iostream>

namespace gui {

Button::Button(ButtonSize s)
{
    m_button.setOutlineThickness(1);
    m_button.setOutlineColor(sf::Color::Green);
    m_button.setFillColor(sf::Color::Black);
    switch (s) {
        case ButtonSize::Wide:
            m_button.setSize({256, 64});
            break;

        case ButtonSize::Small:
            m_button.setSize({128, 64});
            break;
    }
}

void Button::setFunction(std::function<void(void)>func)
{
    m_function = func;
}

void Button::setText (const std::string& str)
{
    m_text.setString(str);
    updateText();
}

void Button::setTexture (const sf::Texture& tex)
{
    m_button.setTexture(&tex);
}

void Button::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
    auto pos = sf::Mouse::getPosition(window);

    switch(e.type) {
        case sf::Event::MouseButtonPressed:
            switch(e.mouseButton.button) {
                case sf::Mouse::Left:
                    if (m_button.getGlobalBounds().contains((float)pos.x, (float)pos.y)) {
                        m_function();
                    }

                default:
                    break;
            }

        default:
            break;
    }
}

void Button::render(sf::RenderTarget& renderer)
{
    renderer.draw(m_button);
    renderer.draw(m_text);
}

void Button::setPosition(const sf::Vector2f& pos)
{
    m_position = pos;

    m_button.setPosition(m_position);
    m_text.setPosition  (m_position);

    updateText();
}

void Button::updateText()
{
    m_text.setOrigin(m_text.getGlobalBounds().width  / 2,
                     m_text.getGlobalBounds().height / 2);

    m_text.move(m_button.getGlobalBounds().width  / 2.0f,
                m_button.getGlobalBounds().height / 2.5f);
}


sf::Vector2f Button::getSize() const
{
    return m_button.getSize();
}

}


constexpr float BASE_Y = 95.0f;

namespace gui
{

StackMenu::StackMenu(const sf::RenderWindow& window, float baseY)
:   m_basePosition  ((float)window.getSize().x / 2.0f, baseY)
,   m_baseSize      (300, 20)
{
    m_background.setOutlineThickness(2);
    m_background.setOutlineColor(sf::Color::Green);
    m_background.setFillColor({100, 100, 100, 230});
    m_background.setSize(m_baseSize);
    m_background.setPosition(m_basePosition.x - m_baseSize.x / 2, baseY - 30);

    m_titleText.setPosition(0, baseY - 35);
    m_titleText.setOutlineColor(sf::Color::Black);
    m_titleText.setOutlineThickness(1);
    m_titleText.setCharacterSize(30);
}

StackMenu::StackMenu(const sf::Vector2f& position)
:   m_basePosition  (position)
,   m_baseSize      (300, 20)
{
    m_background.setFillColor({100, 100, 100, 128});
    m_background.setSize(m_baseSize);
    m_background.setPosition(position);
}

StackMenu::StackMenu(StackMenu&& other)
:   m_widgets       (std::move(other.m_widgets))
,   m_background    (std::move(other.m_background))
,   m_basePosition  (other.m_basePosition)
,   m_baseSize      (other.m_baseSize)
{
}

StackMenu& StackMenu::operator=(StackMenu&& other)
{
    m_widgets       =   std::move(other.m_widgets);
    m_background    =   std::move(other.m_background);
    m_basePosition  =   other.m_basePosition;
    m_baseSize      =   other.m_baseSize;

    return *this;
}

void StackMenu::addWidget(std::unique_ptr<Widget> w)
{
    initWidget(*w);
    m_widgets.push_back(std::move(w));
}

void StackMenu::initWidget(Widget& widget)
{
    widget.setPosition({m_basePosition.x - widget.getSize().x / 2,
                       m_basePosition.y});


    m_basePosition.y    += widget.getSize().y + 25;
    m_baseSize.y        += widget.getSize().y + 25;
    m_background.setSize(m_baseSize);
}

void StackMenu::setTitle(const std::string & title)
{
    m_titleText.setString(title);
    m_titleText.setPosition(Display::WIDTH / 2 - m_titleText.getGlobalBounds().width / 2,
        m_titleText.getPosition().y);
}

void StackMenu::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
    for (auto& widget : m_widgets) {
        widget->handleEvent(e, window);
    }
}

void StackMenu::render(sf::RenderTarget& renderer)
{
    renderer.draw(m_background);
    renderer.draw(m_titleText);
    for (auto& widget : m_widgets) {
        widget->render(renderer);
    }
}

}

#include <iostream>

namespace gui {

TextBox::TextBox(std::string& modString)
:   m_pModString (&modString)
{
    m_label.setCharacterSize(15);
    m_rect.setFillColor({52, 152, 219});
    m_rect.setSize({256, 64});
}

void TextBox::setLabel(const std::string& str)
{
    m_label.setString(str);
}

void TextBox::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
    handleClick     (e, window);
    handleTextInput (e);
}

void TextBox::render(sf::RenderTarget& renderer)
{
    if (!m_isActive) {
        m_rect.setFillColor({52, 152, 219});
    }
    else {
        m_rect.setFillColor({82, 132, 239});
    }
    renderer.draw(m_rect);
    renderer.draw(m_label);
    renderer.draw(m_text);
}

void TextBox::setPosition(const sf::Vector2f& pos)
{
    m_position = pos;

    m_rect.setPosition(m_position);
    m_label.setPosition(m_position.x,
                        m_position.y + m_label.getGlobalBounds().height -
                                       m_rect.getGlobalBounds().height / 2);
    m_text.setPosition  (m_position);
    m_text.move(5, m_rect.getGlobalBounds().height / 2.5f);
}

sf::Vector2f TextBox::getSize() const
{
    return  {m_rect.getSize().x,
             m_rect.getSize().y + m_label.getGlobalBounds().height};
}

void TextBox::handleClick (sf::Event e, const sf::RenderWindow& window)
{
    auto pos = sf::Mouse::getPosition(window);

    if (m_rect.getGlobalBounds().contains((float)pos.x, (float)pos.y))
    {
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                m_isActive = true;
            }
        }
    }
    else
    {
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                m_isActive = false;
            }
        }
    }
}

void TextBox::handleTextInput (sf::Event e)
{
    switch (e.type) {
    case sf::Event::TextEntered:
        if (m_isActive) {
            //Get the key that was entered
            unsigned char keyCode = e.text.unicode;

            if (isValidCharacter(keyCode)) {
                if (m_text.getGlobalBounds().width + 30 <= m_rect.getGlobalBounds().width) {
                    m_pModString->push_back(keyCode);
                }

            }
            else if (isBackspace(keyCode)) {
                //prevents popping back an empty string
                if (m_pModString->length() > 0)
                    m_pModString->pop_back();
            }
            m_text.setString(*m_pModString);
        }
        break;

    default:
        break;
    }
}

bool TextBox::isValidCharacter(unsigned char keyCode)
{
    return  keyCode >= 48 && keyCode <= 57  ||  //Numbers
            keyCode >= 65 && keyCode <= 90  ||  //Uppercase
            keyCode >= 97 && keyCode <= 122 ||  //Lowercase
            keyCode == 32;    //Space
}

bool TextBox::isBackspace(unsigned char keycode)
{
    return keycode == 8;
}


}

namespace gui {

//Text
Widget::Text::Text()
{
    setCharacterSize (25);
    setOutlineColor  (sf::Color::Black);
    setFillColor     (sf::Color::White);
    setFont          (ResourceHolder::get().fonts.get("arcade"));
}

bool Widget::Rectangle::isRolledOn(const sf::RenderWindow& window) const
{
    auto pos = sf::Mouse::getPosition(window);
    return getGlobalBounds().contains((float)pos.x, (float)pos.y);
}

bool Widget::Rectangle::isClicked  (sf::Event e, const sf::RenderWindow& window)
{
    if(isRolledOn(window)) {
        if (e.type == sf::Event::MouseButtonPressed) {
            return e.mouseButton.button == sf::Mouse::Left;
        }
    }
    return false;
}

}

ResourceHolder& ResourceHolder::get()
{
    static ResourceHolder holder;
    return holder;
}

ResourceHolder::ResourceHolder()
:   fonts           ("fonts", "ttf")
,   textures        ("txrs", "png")
,   soundBuffers    ("sfx", "ogg")
{

}


Animation::Animation(unsigned frameWidth, unsigned frameHeight)
: FRAME_WIDTH   (frameWidth)
, FRAME_HEIGHT (frameHeight)
{ }

//Adds a frame...
void Animation::addFrame(unsigned index, sf::Time delay)
{
    sf::IntRect bounds;
    bounds.top = 0;
    bounds.height = FRAME_HEIGHT;
    bounds.width  = FRAME_WIDTH;
    bounds.left   = index * FRAME_WIDTH;

    m_frames.emplace_back(bounds, delay);
}

//Returns the current/active frame of the animation
const sf::IntRect& Animation::getFrame()
{
    if (m_timer.getElapsedTime() >= m_frames[m_framePointer].delay) {
        m_timer.restart();
        m_framePointer++;
        if (m_framePointer == m_frames.size())
            m_framePointer = 0;
    }

    return m_frames[m_framePointer].bounds;
}

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

std::string getFileContent(const std::string& filePath, bool throws)
{
    std::ifstream inFile(filePath);
    if (!inFile.is_open())
    {
        std::string error = "Unable to open file: " + filePath + "!";
        if (throws) {
            throw std::runtime_error(error);
        }
        else {
            std::cerr << error << '\n';
        }
    }

    std::ostringstream stream;
    stream << inFile.rdbuf();
    return stream.str();
}


#include <iostream>

FPSCounter::FPSCounter()
{
    m_text.move(0, 0);
    m_text.setOutlineColor (sf::Color::Black);
    m_text.setFillColor({255,255,255});
    m_text.setOutlineThickness  (2);
    m_text.setFont(ResourceHolder::get().fonts.get("arcade"));
    m_text.setCharacterSize(15);
}

//updates the FPS variable
void FPSCounter::update()
{
    m_frameCount++;

    if (m_delayTimer.getElapsedTime().asSeconds() > 0.2) {
        m_fps = m_frameCount / m_fpsTimer.restart().asSeconds();
        m_frameCount = 0;
        m_delayTimer.restart();
    }
}

//Draws the FPS display to the window
void FPSCounter::draw(sf::RenderTarget& renderer)
{
    m_text.setString("FPS " + std::to_string((int)m_fps));
    renderer.draw(m_text);
}

ToggleKey::ToggleKey(sf::Keyboard::Key key)
:   m_key (key)
{ }

bool ToggleKey::isKeyPressed()
{
    if (m_delayTimer.getElapsedTime().asSeconds() > 0.2) {
        if (sf::Keyboard::isKeyPressed(m_key)) {
            m_delayTimer.restart();
            return true;
        }
    }
    return false;
}

namespace SpaceInvaders
{
    AnimationRenderer::AnimationRenderer(int frameWidth, int frameHeight, float entityWidth, float entityHeight, const sf::Texture & spriteSheet)
        : m_frameWidth(frameWidth)
        , m_frameHeight(frameHeight)
    {
        m_entity.setSize({ entityWidth, entityHeight });
        m_entity.setTexture(&spriteSheet);
    }

    void AnimationRenderer::nextFrame()
    {
        m_currentFrame++;
    }

    void AnimationRenderer::renderEntity(sf::RenderTarget & renderer, int type, const sf::Vector2f & position)
    {
        //Calculate texture coords
        int texLeft = (m_currentFrame % 2) * m_frameWidth;
        int texTop = (type * m_frameHeight);

        //Reposition and draw sprite
        m_entity.setPosition(position);
        m_entity.setTextureRect({ texLeft, texTop, m_frameWidth, m_frameHeight });
        renderer.draw(m_entity);
    }
}

namespace SpaceInvaders
{
    Collidable::Collidable(float width, float height)
        : m_size(width, height)
    {}

    bool Collidable::tryCollideWith(Collidable & other)
    {
        if (getBox().intersects(other.getBox())) {
            onCollide(other);
            other.onCollide(*this);
            return true;
        }
        return false;
    }

    sf::FloatRect Collidable::getBox() const
    {
        return
        {
            getPosition().x,
            getPosition().y,
            m_size.x,
            m_size.y
        };
    }
}

namespace SpaceInvaders
{
    Explosion::Explosion(const sf::Vector2f & position)
        : m_position(position)
    {
    }

    bool Explosion::isLifeOver() const
    {
        return m_lifetimeCounter.getElapsedTime().asSeconds() >= 0.2f;
    }

    const sf::Vector2f & Explosion::getPosition() const
    {
        return m_position;
    }
}

namespace SpaceInvaders
{
    Invader::Invader(const sf::Vector2f & initialLocation, Type type)
        : Collidable(WIDTH, HEIGHT)
        , m_location(initialLocation)
        , m_type(type)
        , m_initialPosition(initialLocation)
    {
    }

    void Invader::move(float x, float y)
    {
        m_location += {x, y};
    }

    const sf::Vector2f & Invader::getPosition() const
    {
        return m_location;
    }

    bool Invader::isAlive() const
    {
        return m_isAlive;
    }

    Invader::Type Invader::getType() const
    {
        return m_type;
    }

    void Invader::onCollide(Collidable& other)
    {
        m_isAlive = false;
    }
}

namespace SpaceInvaders
{
    namespace
    {
        constexpr float BASE_Y = (float)Display::HEIGHT - 40.0f;
    }

    Player::Player()
        : Collidable(44, 32)
        , m_deathAnimation(11, 8)
    {
        m_sprite.setSize({ 44, 32 });
        m_sprite.setPosition({ Display::WIDTH / 2, BASE_Y });
        m_sprite.setTexture(&ResourceHolder::get().textures.get("si/player"));
        m_sprite.setTextureRect({ 0, 0, 11, 8 });

        for (int i = 0; i < 20; i++) {
            m_deathAnimation.addFrame(((i % 2) + 1), sf::seconds(0.1f));
        }

        m_deathSound.setBuffer(ResourceHolder::get().soundBuffers.get("si/explosion"));

    }

    void Player::restart()
    {
        m_velocity *= 0.0f;
        m_sprite.setTextureRect({ 0, 0, 11, 8 });
        m_isAlive = true;
        m_livesLeft--;
        m_sprite.setPosition({ Display::WIDTH / 2, BASE_Y });
    }

    void Player::input()
    {
        using Key = sf::Keyboard::Key;
        auto keyDown = [](sf::Keyboard::Key k) {
            return sf::Keyboard::isKeyPressed(k);
        };

        float speed = 20;
        if (keyDown(Key::A)) {
            m_velocity.x -= speed;
        }
        else if (keyDown(Key::D)) {
            m_velocity.x += speed;
        }
    }

    void Player::update(float dt)
    {
        if (m_isAlive) {
            auto w = m_sprite.getGlobalBounds().width;
            m_sprite.move(m_velocity * dt);
            m_velocity *= 0.95f;
            if (m_sprite.getPosition().x <= 0) {
                m_velocity.x = 1.0f;
                m_sprite.setPosition(1.0f, BASE_Y);
            }
            else if (m_sprite.getPosition().x + w >= Display::WIDTH) {
                m_velocity.x = -1.0f;
                m_sprite.setPosition(Display::WIDTH - 1.0f - w, BASE_Y);
            }
        }
    }

    void Player::draw(sf::RenderTarget& target)
    {
        if (!m_isAlive) {
            m_sprite.setTextureRect(m_deathAnimation.getFrame());
        }
        if (m_livesLeft >= 0) {
            target.draw(m_sprite);
        }
    }

    sf::Vector2f Player::getGunPosition() const
    {
        return
        {
            m_sprite.getPosition().x + m_sprite.getGlobalBounds().width / 2,
            m_sprite.getPosition().y
        };
    }

    const sf::Vector2f & Player::getPosition() const
    {
        return m_sprite.getPosition();
    }

    void Player::onCollide(Collidable& other)
    {
        m_isAlive = false;
        m_deathTimer.restart();
        m_deathSound.play();
    }

    int Player::getLives() const
    {
        return m_livesLeft;
    }

    bool Player::isAlive() const
    {
        return m_isAlive;
    }

    void Player::tryRevive()
    {
        if (m_deathTimer.getElapsedTime().asSeconds() >= 1.5f) {
            restart();
        }

    }

}


namespace SpaceInvaders
{
    Projectile::Projectile(const sf::Vector2f & position, Type type, Direction direction)
        : Collidable(WIDTH / 1.5, HEIGHT)
        , m_position(position)
        , m_type(type)
        , m_direction(direction)
    {
        static int ID = 0;
        m_id = ID++;
    }

    void Projectile::update(float dt)
    {
        float speed = 650 * (float)m_direction * dt;
        m_position.y += speed;
        if (m_position.y <= 0 || m_position.y >= Display::HEIGHT) {
            destroy();
        }
    }

    void Projectile::onCollide(Collidable& other)
    {
        destroy();
    }

    void Projectile::destroy()
    {
        m_isActive = false;
    }

    const sf::Vector2f & Projectile::getPosition() const
    {
        return m_position;
    }

    Projectile::Type Projectile::getType() const
    {
        return m_type;
    }

    bool Projectile::isActive() const
    {
        return m_isActive;
    }

    Projectile::Direction Projectile::getDirection() const
    {
        return m_direction;
    }

    int Projectile::getID() const
    {
        return m_id;
    }
}


#include <iostream>

namespace SpaceInvaders
{
    Shield::Shield(float x)
        : Collidable((float)SIZE, (float)SIZE)
        , m_position(x, Display::HEIGHT - 200)
    {
        using Sty = SectorStyle;
        for (float sy = 0; sy < 4; sy++) {
            for (float sx = 0; sx < 4; sx++) {
                Sty style = Sty::Square;
                int xP = (int)sx;
                int yP = (int)sy;
                if (xP == 0 && yP == 0) style = Sty::SlopeUp;
                if (xP == 3 && yP == 0) style = Sty::SlopeDown;
                if (xP == 1 && yP == 3) style = Sty::SlopeUnderUp;
                if (xP == 2 && yP == 3) style = Sty::SlopeUnderDown;

                m_sections.emplace_back(x + sx * SECT_SIZE,
                    m_position.y + sy * SECT_SIZE, style);
            }
        }
    }

    void Shield::draw(sf::RenderTarget & target)
    {
        for (auto& sect : m_sections) {
            sect.draw(target);
        }
    }

    const sf::Vector2f & Shield::getPosition() const
    {
        return m_position;
    }

    Shield::ShieldSection& Shield::getSection(int x, int y)
    {
        return m_sections[y * 4 + x];
    }

    void Shield::destroyPoint(float relX, float relY)
    {
        //Test for out of bounds
        if (relX < 0 || relX >= SIZE ||
            relY < 0 || relY >= SIZE) return;

        //Get section this is inside of
        int xIndex = (int)relX / SECT_SIZE;
        int yIndex = (int)relY / SECT_SIZE;
        auto& section = getSection(xIndex, yIndex);
        auto& sectionPos = section.getPosition();

        //Transform to find the pixel coordinate
        float sectionTopLeftX = sectionPos.x - m_position.x;
        float sectionTopLeftY = sectionPos.y - m_position.y;
        float pixelX = relX - sectionTopLeftX;
        float pixelY = relY - sectionTopLeftY;

        //DESTROY
        section.destroyArea((int)pixelX, (int)pixelY);
    }


    bool Shield::isTouching(const Projectile& projectile)
    {
        static Random<> rand;
        if (projectile.getBox().intersects(getBox())) {
            for (auto& sector : m_sections) {
                auto result = sector.isTouching(projectile);
                if ((int)result.x == -1)
                    continue;
                else { //This means the projectile is touching the shield

                    //Get coordinate of collision point relative to top left of sheild
                    result.x -= m_position.x;
                    result.y -= m_position.y;

                    //Destory around point of collision
                    for (int y = -3; y < 3; y++) {
                        for (int x = -3; x < 3; x++) {
                            float newRelativeX = result.x + x * 2;
                            float newRelativeY = result.y + y * 2;
                            destroyPoint(newRelativeX, newRelativeY);
                        }
                    }

                    //blast damge
                    float radius = 12.0f;
                    for (int i = 0; i < 35; i++) {
                        float newRelativeX = result.x + rand.getFloatInRange(-radius, radius);
                        float newRelativeY = result.y + rand.getFloatInRange(-radius, radius);
                        destroyPoint(newRelativeX, newRelativeY);
                    }
                    return true;
                }
            }
        }
        return false;
    }

    Shield::ShieldSection::ShieldSection(float tlX, float tlY, SectorStyle style)
        : Collidable((float)SECT_SIZE, (float)SECT_SIZE)
        , m_position({ tlX, tlY })
    {
        for (float y = 0; y < SECT_SIZE; y++) {
            for (float x = 0; x < SECT_SIZE; x++) {
                sf::Vertex pixel;
                pixel.color = sf::Color::Green;
                pixel.position = { x + tlX, y + tlY };
                calculatePixelCoord((int)x, (int)y, pixel, style);
            }
        }
    }

    void Shield::ShieldSection::draw(sf::RenderTarget & target)
    {
        target.draw(m_pixels.data(), m_pixels.size(), sf::Points);
    }

    const sf::Vector2f & Shield::ShieldSection::getPosition() const
    {
        return m_position;
    }

    sf::Vector2f Shield::ShieldSection::isTouching(const  Projectile & other)
    {
        for (auto& px : m_pixels) {
            if (other.getBox().contains(px.position) && px.color == sf::Color::Green) {
                return px.position;
            }
        }
        return { -1, -1 };
    }

    //Blacks out an area around the inputted point
    void Shield::ShieldSection::destroyArea(int x, int y)
    {
        for (int oY = -2; oY <= 2; oY++) {
            for (int oX = -2; oX <= 2; oX++) {
                int newX = x + oX;
                int newY = y + oY;
                if (newX < 0 || newX >= SECT_SIZE ||
                    newY < 0 || newY >= SECT_SIZE) continue;
                m_pixels[newY * SECT_SIZE + newX].color = sf::Color::Black;
            }
        }
    }

    void Shield::ShieldSection::calculatePixelCoord(int x, int y, sf::Vertex & pixel, SectorStyle style)
    {
        switch (style) {
        case SectorStyle::Square:
            m_pixels[y * SECT_SIZE + x] = pixel;
            break;

        case SectorStyle::SlopeUp:
            if (SECT_SIZE - y < x) {
                m_pixels[y * SECT_SIZE + x] = pixel;
            }
            break;

        case SectorStyle::SlopeDown:
            if (x < y) {
                m_pixels[y * SECT_SIZE + x] = pixel;
            }
            break;

        case SectorStyle::SlopeUnderUp:
            if (SECT_SIZE - x > y) {
                m_pixels[y * SECT_SIZE + x] = pixel;
            }
            break;

        case SectorStyle::SlopeUnderDown:
            if (x > y) {
                m_pixels[y * SECT_SIZE + x] = pixel;
            }
            break;
        }
    }
}


namespace SpaceInvaders
{
    namespace
    {
        constexpr float WIDTH = 72;
        constexpr float HEIGHT = 36;
        constexpr float Y_POS = 45;
    }

    UFO::UFO(Random<>& rand)
        : Collidable(WIDTH, HEIGHT)
        , m_rng(rand)
        , m_animation(16, 8)
    {
        m_sprite.setSize({ WIDTH, HEIGHT });
        m_sprite.setPosition((float)Display::WIDTH, Y_POS);
        m_sprite.setTexture(&ResourceHolder::get().textures.get("si/ufo"));

        for (int i = 0; i < 3; i++) {
            m_animation.addFrame(i, sf::seconds(0.2f));
        }
        m_flyingSound.setBuffer(ResourceHolder::get().soundBuffers.get("si/ufo_lowpitch"));
        m_flyingSound.setVolume(10);
    }

    UFO::State UFO::getState() const
    {
        return m_state;
    }

    void UFO::update(float dt)
    {
        switch (m_state) {
        case State::Destroyed:
            m_state = State::Waiting;
            break;

        case State::Flying:
            m_sprite.move(m_vx * dt, 0);
            if (getPosition().x <= -WIDTH || getPosition().x >= Display::WIDTH + WIDTH) {
                m_state = State::Waiting;
            }
            if ((int)m_flyingSound.getStatus() != (int)sf::Sound::Status::Playing ||
                m_flyingSound.getPlayingOffset() >= sf::seconds(1.5)) {
                m_flyingSound.setPlayingOffset(sf::seconds(0.2f));
                m_flyingSound.play();
            }
            break;

        case State::Waiting:
            if (m_rng.getIntInRange(1, 250) == 100) {
                m_state = State::Flying;
                m_vx = (float)m_rng.getIntInRange(-1, 1) * 200.0f;
                float xPos;
                if (m_vx >= 0) {
                    xPos = -WIDTH;
                }
                else {
                    xPos = Display::WIDTH;
                }
                m_sprite.setPosition(xPos, Y_POS);
            }
            break;
        }
    }

    void UFO::draw(sf::RenderTarget & window)
    {
        if (m_state == State::Flying) {
            m_sprite.setTextureRect(m_animation.getFrame());
            window.draw(m_sprite);
        }
    }

    const sf::Vector2f & UFO::getPosition() const
    {
        return m_sprite.getPosition();
    }

    void UFO::onCollide(Collidable & other)
    {
        m_state = State::Destroyed;
        m_sprite.setPosition(-1000, 0); //Move offscreen so it cannot be collided with projectiles
    }
}

#include <iostream>


namespace SpaceInvaders
{
    namespace
    {
        const int MAX_INVADERS = 55;
    }

    InvaderManager::InvaderManager(World& world)
        : m_stepGap(sf::seconds(0.5f))
        , m_world(world)
        , m_invaderRenderer(12, 8, Invader::WIDTH, Invader::HEIGHT,
            ResourceHolder::get().textures.get("si/invaders"))
    {
        //Layout of the invaders 
        Invader::Type types[] = {
            Invader::Type::Squid, Invader::Type::Crab, Invader::Type::Crab,
            Invader::Type::Octopus, Invader::Type::Octopus
        };
        //Add invaders into the std::vector
        const int GAP = 10;
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 11; x++) {
                //calcuate position for invader
                float invaderX = x * Invader::WIDTH + (GAP  * x * 3) + Invader::WIDTH;
                float invaderY = y * Invader::HEIGHT + (GAP * y) + Invader::HEIGHT * 4;
                m_invaders.emplace_back(sf::Vector2f{ invaderX, invaderY }, types[y]);
            }
        }

        //load sounds
        for (int i = 0; i < 4; i++) {
            m_stepSounds[i].setBuffer(
                ResourceHolder::get().soundBuffers.get("si/fastinvader" + std::to_string(i + 1)));
        }
        m_invaderKilledSound.setBuffer(
            ResourceHolder::get().soundBuffers.get("si/invaderkilled"));


    }

    void InvaderManager::tryStepInvaders()
    {
        //Only step if clock is over timer
        if (m_stepTimer.getElapsedTime() > m_stepGap) {
            m_invaderRenderer.nextFrame();
            //Calculate amount to step
            bool moveDown = false;
            float step = m_isMovingLeft ? -10.0f : 10.0f;
            if (m_moveDown) {
                step *= -1;
            }
            m_stepSounds[m_ticks++ % 4].play();

            //Move the invaders
            for (auto& invader : m_invaders) {
                if (!invader.isAlive()) continue;
                invader.move(step, 0.0f);
                if (m_moveDown) {
                    invader.move(0, Invader::HEIGHT / 2.0f);
                }
                else if (!moveDown) {
                    //Check invader position to see if all should move down
                    moveDown = testInvaderPosition(invader);
                }
            }

            if (m_moveDown) m_isMovingLeft = !m_isMovingLeft;
            m_moveDown = moveDown;
            m_stepTimer.restart();
        }
    }

    void InvaderManager::drawInvaders(sf::RenderTarget& target)
    {
        for (auto& invader : m_invaders) {
            if (!invader.isAlive()) continue;
            m_invaderRenderer.renderEntity(target, (int)invader.getType(), invader.getPosition());
        }
    }

    CollisionResult InvaderManager::tryCollideWithProjectiles(std::vector<Projectile>& projectiles)
    {
        CollisionResult result;
        std::vector<sf::Vector2f> collisionPoints;
        for (auto& projectile : projectiles) {
            for (auto& invader : m_invaders) {
                if (!invader.isAlive() || !projectile.isActive())
                    continue;
                if (projectile.tryCollideWith(invader)) {
                    m_aliveInvaders--;
                    m_invaderKilledSound.play();
                    if (m_aliveInvaders == 0) {
                        m_hasAllInvadersBeenAdded = false;
                    }
                    result.second.emplace_back(invader.getPosition());
                    result.first += ((int)invader.getType() + 1) * 100;
                    updateStepDelay();
                }
            }
        }
        return result;
    }

    sf::Vector2f InvaderManager::getRandomLowestInvaderPoint(Random<>& random)
    {
        if (m_aliveInvaders == 0) return { -1, -1 };
        //Keep looping until an invader is found
        while (true) {
            auto invaderColumn = random.getIntInRange(0, 10);
            for (int y = 4; y >= 0; y--) {
                int index = y * 11 + invaderColumn;
                auto& invader = m_invaders.at(index);
                if (invader.isAlive()) {
                    return {
                        //transform to below the invader's center
                        invader.getPosition().x + Invader::WIDTH / 2,
                        invader.getPosition().y + Invader::HEIGHT + 5
                    };
                }
            }
        }
    }

    int InvaderManager::getAliveInvadersCount() const
    {
        return m_aliveInvaders;
    }

    //Adds invaders to scene 1 at a time
    void InvaderManager::initAddInvader()
    {
        static sf::Clock delay;
        if (delay.getElapsedTime().asSeconds() > 0.02) {
            m_invaders.at(m_initY * 11 + m_initX).makeAlive();
            m_aliveInvaders++;
            m_initX++;
            if (m_initX == 11) {
                m_initX = 0;
                m_initY--;
            }
            delay.restart();
        }

        if (m_aliveInvaders == MAX_INVADERS) {
            m_hasAllInvadersBeenAdded = true;
            m_initX = 0;
            m_initY = 4;
            updateStepDelay();
        }
    }

    bool InvaderManager::areInvadersAlive() const
    {
        return m_hasAllInvadersBeenAdded;
    }

    void InvaderManager::updateStepDelay()
    {
        m_stepGap = sf::seconds((float)m_aliveInvaders / 90.0f);
    }

    bool InvaderManager::testInvaderPosition(const Invader& invader) const
    {
        if (invader.getPosition().y > Display::HEIGHT - 150) {
            m_world.setGameIsOver();
        }
        return
            (invader.getPosition().x < 15 && m_isMovingLeft) || //Check invader left
            (invader.getPosition().x + Invader::WIDTH > Display::WIDTH - 15 && !m_isMovingLeft); //Check invader right
    }
}


namespace SpaceInvaders
{
    StarryBackground::StarryBackground()
    {
        for (int i = 0; i < 500; i++) {
            sf::Vertex star;
            giveStarRandomStartLocation(star);
            star.position.y -= Display::HEIGHT;
            m_stars.push_back(star);
        }
    }

    void StarryBackground::update(float dt)
    {
        for (auto& star : m_stars) {
            star.position.y -= 250 * dt;
            if (star.position.y <= 0) {
                giveStarRandomStartLocation(star);
            }
        }
    }

    void StarryBackground::draw(sf::RenderTarget & renderer)
    {
        renderer.draw(m_stars.data(), m_stars.size(), sf::Points);
    }

    void StarryBackground::giveStarRandomStartLocation(sf::Vertex & star)
    {
        star.position = { m_rng.getFloatInRange(0, (float)Display::WIDTH),
            m_rng.getFloatInRange((float)Display::HEIGHT, (float)Display::HEIGHT  * 2.0f) };
    }
}


#include <fstream>
#include <sstream>
#include <iostream>


namespace SpaceInvaders
{
    namespace
    {
        const auto scoresPath = "res/si/scores.txt";
    }

    StateHighscores::StateHighscores(Game & game, int score)
        : StateHighscores(game)
    {
        initSubmitMenu();
        m_scoreToSubmit = score;
        m_pActiveMenu = &m_submitScoreMenu;
        m_state = State::Submitting;
    }

    StateHighscores::StateHighscores(Game & game)
        : StateBase(game, "Highscores")
        , m_submitScoreMenu(game.getWindow(), 100.0f)
        , m_highscoreMenu(game.getWindow(), Display::HEIGHT - 100.0f)
        , m_state(State::Viewing)
    {
        initViewMenu();
        m_pActiveMenu = &m_highscoreMenu;
        m_banner.setSize({ (float)Display::WIDTH, 200 });
        m_banner.setTexture(&ResourceHolder::get().textures.get("si/highscores"));
        createHighscoreView();
    }

    void StateHighscores::handleEvent(sf::Event e)
    {
        m_pActiveMenu->handleEvent(e, m_pGame->getWindow());
    }

    void StateHighscores::update(sf::Time deltaTime)
    {
        m_background.update(deltaTime.asSeconds());
    }

    void StateHighscores::render(sf::RenderTarget & renderer)
    {
        m_background.draw(renderer);
        m_pActiveMenu->render(renderer);
        if (m_state == State::Viewing) {
            for (auto& entry : m_entryBoxes) {
                entry.draw(renderer);
            }
            renderer.draw(m_banner);
        }
    }

    int StateHighscores::getHighestScore()
    {
        std::ifstream inFile(scoresPath);
        std::string buffer;

        std::getline(inFile, buffer, ',');
        std::getline(inFile, buffer, ',');
        if (buffer.empty()) return 0;
        else return std::stoi(buffer);
    }

    void StateHighscores::initViewMenu()
    {
        loadScores();

        auto backBtn = gui::makeButton();
        backBtn->setText("Main Menu");
        backBtn->setFunction([&]() {
            m_pGame->popState();
        });
        m_highscoreMenu.addWidget(std::move(backBtn));
    }

    void StateHighscores::initSubmitMenu()
    {
        auto nameTextBox = gui::makeTextBox(m_submitString);
        nameTextBox->setLabel("Click text box to enter name");

        auto submitBtn = gui::makeButton();
        submitBtn->setText("Submit Score");
        submitBtn->setFunction([&]() {
            if (!m_submitString.empty()) {
                submitScore();
                switchToViewMenu();
            }
        });


        auto backBtn = gui::makeButton();
        backBtn->setText("View HighScores");
        backBtn->setFunction([&]() {
            loadScores();
            switchToViewMenu();
        });

        m_submitScoreMenu.addWidget(std::move(nameTextBox));
        m_submitScoreMenu.addWidget(std::move(submitBtn));
        m_submitScoreMenu.addWidget(std::move(backBtn));
    }

    void StateHighscores::switchToViewMenu()
    {
        m_state = State::Viewing;
        m_pActiveMenu = &m_highscoreMenu;
        createHighscoreView();
    }

    void StateHighscores::createHighscoreView()
    {
        loadScores();
        sortScores();
        m_entryBoxes.clear();
        for (unsigned i = 0; i < m_scores.size(); i++) {
            auto& name = m_scores[i].first;
            auto score = m_scores[i].second;

            m_entryBoxes.emplace_back(i + 1, name, score);
            if (i >= 9) return; //Only show top 10 scores
        }
    }

    void StateHighscores::loadScores()
    {
        m_scores.clear();
        std::ifstream inFile(scoresPath);
        std::string line;
        int switcher = 0;
        std::string name;
        int score;
        while (std::getline(inFile, line, ',')) {
            if (switcher++ % 2 == 0) {
                name = line;
            }
            else {
                score = std::stoi(line);
                m_scores.emplace_back(std::make_pair(name, score));
            }
        }
        sortScores();
    }

    void StateHighscores::writeScores()
    {
        sortScores();
        std::ofstream outFile(scoresPath);
        for (auto& entry : m_scores) {
            outFile << entry.first << "," << entry.second << ",";
        }
    }

    void StateHighscores::sortScores()
    {
        std::sort(m_scores.begin(), m_scores.end(), [](Entry& a, Entry& b) {
            return a.second > b.second;
        });
    }

    void StateHighscores::submitScore()
    {
        loadScores();
        m_scores.emplace_back(std::make_pair(m_submitString, m_scoreToSubmit));
        writeScores();
    }

    StateHighscores::EntryBox::EntryBox(int position, const std::string & name, int score)
    {
        float size = 35;
        float y = 200 + position * (size - 2);
        m_background.setSize({ Display::WIDTH / 1.5f, size });
        m_background.setPosition({ Display::WIDTH / 2 - m_background.getGlobalBounds().width / 2, y });

        m_nameText.setCharacterSize((unsigned)size - 5);
        m_scoreText.setCharacterSize((unsigned)size - 5);

        m_nameText.setString(std::to_string(position) + "     " + name);
        m_scoreText.setString(std::to_string(score));

        m_nameText.setPosition(m_background.getPosition());
        m_scoreText.setPosition(m_background.getPosition().x +
            m_background.getGlobalBounds().width -
            m_scoreText.getGlobalBounds().width - 10,
            y);

        m_background.setOutlineThickness(2);
        m_background.setOutlineColor(sf::Color::Green);
        m_background.setFillColor(
            position % 2 == 0 ?
            sf::Color::Black :
            sf::Color{ 50, 40, 50 }
        );
    }

    void StateHighscores::EntryBox::draw(sf::RenderTarget & renderer)
    {
        renderer.draw(m_background);
        renderer.draw(m_nameText);
        renderer.draw(m_scoreText);
    }
}



namespace SpaceInvaders
{
    StateMainMenu::StateMainMenu(Game & game)
        : StateBase(game, "Main Menu")
        , m_mainMenu(game.getWindow(), Display::HEIGHT / 2 - 100)
    {
        m_banner.setSize({ (float)Display::WIDTH, 200 });
        m_banner.setTexture(&ResourceHolder::get().textures.get("si/logo"));


        auto playBtn = gui::makeButton();
        playBtn->setText("Play game");
        playBtn->setFunction([&]() {
            m_pGame->pushState<StatePlaying>(*m_pGame);
        });

        auto highscoresBtn = gui::makeButton();
        highscoresBtn->setText("Highscores");
        highscoresBtn->setFunction([&]() {
            m_pGame->pushState<StateHighscores>(*m_pGame);
        });

        auto exitBtn = gui::makeButton();
        exitBtn->setText("Exit game");
        exitBtn->setFunction([&]() {
            m_pGame->exitGame();
        });

        m_mainMenu.addWidget(std::move(playBtn));
        m_mainMenu.addWidget(std::move(highscoresBtn));
        m_mainMenu.addWidget(std::move(exitBtn));
        m_mainMenu.setTitle("Choose Action");
    }

    void StateMainMenu::handleEvent(sf::Event e)
    {
        m_mainMenu.handleEvent(e, m_pGame->getWindow());
    }

    void StateMainMenu::update(sf::Time deltaTime)
    {
        m_background.update(deltaTime.asSeconds());
    }

    void StateMainMenu::render(sf::RenderTarget & renderer)
    {
        m_background.draw(renderer);
        m_mainMenu.render(renderer);
        renderer.draw(m_banner);
    }
}


#include <iostream>



namespace SpaceInvaders
{
    StatePlaying::StatePlaying(Game& game)
        : StateBase(game, "Playing the game")
        , m_gameOverMenu(game.getWindow(), Display::HEIGHT / 3)
        , m_scoreDisplay(Display::WIDTH / 8, "Score")
        , m_highestScoreDisplay(Display::WIDTH / 2, "HighScore")
    {

        auto mmButton = std::make_unique<gui::Button>();
        mmButton->setText("Main Menu\n");
        mmButton->setFunction([&]() {
            m_pGame->popState();
        });

        auto submitBtn = std::make_unique<gui::Button>();
        submitBtn->setText("Submit Score");
        submitBtn->setFunction([&]() {
            m_pGame->changeState<StateHighscores>(*m_pGame, m_score);
        });

        auto exitButton = std::make_unique<gui::Button>();
        exitButton->setText("Exit game\n");
        exitButton->setFunction([&]() {
            m_pGame->exitGame();
        });

        m_gameOverMenu.setTitle("GAME  OVER");
        m_gameOverMenu.addWidget(std::move(mmButton));
        m_gameOverMenu.addWidget(std::move(submitBtn));
        m_gameOverMenu.addWidget(std::move(exitButton));

        m_highestScoreDisplay.update(StateHighscores::getHighestScore());
    }

    void StatePlaying::handleEvent(sf::Event e)
    {
        if (m_isGameover) {
            m_gameOverMenu.handleEvent(e, m_pGame->getWindow());
        }
    }

    void StatePlaying::handleInput()
    {
        m_world.input();
    }

    void StatePlaying::update(sf::Time deltaTime)
    {
        if (!m_isGameover) {
            m_score += m_world.update(deltaTime.asSeconds());
            m_scoreDisplay.update(m_score);

            if (m_score > m_highestScoreDisplay.getCurrentScoreDisplayed()) {
                m_highestScoreDisplay.update(m_score);
            }
        }

        m_isGameover = m_world.isGameOver();
    }


    void StatePlaying::render(sf::RenderTarget& renderer)
    {
        m_world.draw(renderer);

        m_lifeDisplay.draw(renderer, m_world.getPlayer().getLives());
        m_scoreDisplay.draw(renderer);
        m_highestScoreDisplay.draw(renderer);

        if (m_isGameover) {
            m_gameOverMenu.render(renderer);
        }
    }

    ///////////////////////////////////////////////
    //     display member functions       ///
    StatePlaying::LifeDisplay::LifeDisplay()
    {
        m_lifeStamp.setSize({ Player::WIDTH / 2, Player::WIDTH / 2 });
        m_lifeStamp.setTexture(&ResourceHolder::get().textures.get("si/player"));
        m_lifeStamp.setTextureRect({ 0, 0, 11, 8 });
        m_label.setPosition(Display::WIDTH - (Player::WIDTH * 5), 10);
        m_label.setString("LIVES");
        m_label.setOutlineThickness(0);
    }

    void StatePlaying::LifeDisplay::draw(sf::RenderTarget& window, int lives)
    {
        float xOrigin = m_label.getPosition().x +
            m_label.getGlobalBounds().width + 10;
        float yOrigin = m_label.getPosition().y +
            m_label.getGlobalBounds().height / 2;

        window.draw(m_label);
        for (int i = 0; i < lives; i++) {
            m_lifeStamp.setPosition(xOrigin + i * Player::WIDTH / 2 + i * 10, yOrigin);
            window.draw(m_lifeStamp);
        }
    }

    StatePlaying::ScoreDisplay::ScoreDisplay(float x, const std::string& text)
        : m_text(text)
        , m_centerPosition(x)
    {
        updateDisplay();
        m_label.setOutlineThickness(0);
    }

    void StatePlaying::ScoreDisplay::update(int newScore)
    {
        m_currentScore = newScore;
        updateDisplay();
    }

    void StatePlaying::ScoreDisplay::draw(sf::RenderTarget & target)
    {
        target.draw(m_label);
    }

    int StatePlaying::ScoreDisplay::getCurrentScoreDisplayed() const
    {
        return m_currentScore;
    }

    void StatePlaying::ScoreDisplay::updateDisplay()
    {
        m_label.setString(m_text + "   " + std::to_string(m_currentScore));
        m_label.setPosition(m_centerPosition - m_label.getGlobalBounds().width / 2, 15);
    }
}

namespace SpaceInvaders
{
    World::World()
        : m_projectileRenderer(4, 8, Projectile::WIDTH, Projectile::HEIGHT,
            ResourceHolder::get().textures.get("si/projectile"))
        , m_ufo(m_rng)
        , m_invaders(*this)
    {
        m_explodeShape.setSize({ 52, 28 });
        m_explodeShape.setTexture(&ResourceHolder::get().textures.get("si/explosion"));

        const int SECT_SIZE = (Display::WIDTH / 4);
        for (int i = 0; i < 4; i++) {

            m_shields.emplace_back(float(i * SECT_SIZE + SECT_SIZE / 2 - Shield::SIZE / 2));
        }

        m_playerShoot.setBuffer(ResourceHolder::get().soundBuffers.get("si/shoot"));
        m_playerShoot.setVolume(25);
    }

    void World::input()
    {
        if (m_player.isAlive()) {
            if (m_invaders.areInvadersAlive()) {
                m_player.input();
                playerProjectileInput();
            }
        }
        else {
            m_player.tryRevive();
        }
    }

    int World::update(float dt)
    {
        int score = 0;

        if (m_invaders.areInvadersAlive()) {
            m_player.update(dt);
            if (m_player.isAlive()) {
                m_invaders.tryStepInvaders();
                enemyProjectileFire();

                //pair of score gained and points of collision list
                auto collisionResult = getCollisionResult(dt);
                if (collisionResult.second.size() > 0) {
                    score += collisionResult.first;
                    for (auto& point : collisionResult.second) {
                        m_explosions.emplace_back(point);
                    }
                }

                m_ufo.update(dt);
            }

            for (auto itr = m_explosions.begin(); itr != m_explosions.end();) {
                if (itr->isLifeOver()) itr = m_explosions.erase(itr);
                else itr++;
            }
        }
        else {
            m_invaders.initAddInvader();
            m_projectiles.clear();
            m_explosions.clear();
        }
        return score;
    }

    const Player & World::getPlayer() const
    {
        return m_player;
    }

    bool World::isGameOver() const
    {
        return m_player.getLives() == -1 || m_isGameOver;
    }

    //TODO GENERALISE THESE TWO FUNCTIONS VV
    void World::playerProjectileInput()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
            m_playerShotClock.getElapsedTime().asSeconds() > 0.5f) {
            auto point = m_player.getGunPosition();
            point.y -= Projectile::HEIGHT;
            point.x -= Projectile::WIDTH / 2.0f;
            m_projectiles.emplace_back(point, Projectile::Type::Rectangle, Projectile::Direction::Up);
            m_playerShotClock.restart();
            m_playerShoot.play();
        }
    }

    void World::enemyProjectileFire()
    {
        if (m_invaderShotClock.getElapsedTime().asSeconds() >= 0.1 &&
            m_rng.getIntInRange(0, 30) == 2) {
            auto point = m_invaders.getRandomLowestInvaderPoint(m_rng);
            if ((int)point.x == -1) return;
            auto type = static_cast<Projectile::Type>(m_rng.getIntInRange(1, 2));
            m_projectiles.emplace_back(point, type, Projectile::Direction::Down);
            m_invaderShotClock.restart();
        }
    }
    //end of to-do

    CollisionResult World::getCollisionResult(float dt)
    {
        auto result = m_invaders.tryCollideWithProjectiles(m_projectiles);
        updateProjectiles(dt, result.second);

        for (auto& projectile : m_projectiles) {

            //Projectile verses sheild collisons
            for (auto& sheild : m_shields) {
                if (sheild.isTouching(projectile)) {
                    projectile.destroy();
                    result.second.emplace_back(projectile.getPosition());
                }
            }

            //Projectile verses UFO collisons
            if (m_ufo.tryCollideWith(projectile)) {
                result.second.emplace_back(projectile.getPosition());
                result.first += 200;
            }

            //Projectile verses projectile collisions
            for (auto& otherProjectile : m_projectiles) {
                if (otherProjectile.getID() != projectile.getID()) {
                    if (otherProjectile.tryCollideWith(projectile)) {
                        result.second.emplace_back(projectile.getPosition());
                    }
                }
            }
        }


        return result;
    }

    void World::updateProjectiles(float dt, std::vector<sf::Vector2f>& collisionPoints)
    {
        for (auto itr = m_projectiles.begin(); itr != m_projectiles.end();) {
            auto& projectile = *itr;
            if (!projectile.isActive()) {
                itr = m_projectiles.erase(itr);
            }
            else {
                //Test for player getting hit 
                if (projectile.tryCollideWith(m_player)) {
                    collisionPoints.emplace_back(m_player.getGunPosition());
                    m_projectiles.clear();
                    return;
                }
                projectile.update(dt);
                itr++;
            }
        }
    }

    void World::draw(sf::RenderTarget & target)
    {
        if (m_animTimer.getElapsedTime().asSeconds() > 0.2) {
            m_projectileRenderer.nextFrame();
            m_animTimer.restart();
        }

        for (auto& shield : m_shields) {
            shield.draw(target);
        }

        for (auto& proj : m_projectiles) {
            m_projectileRenderer.renderEntity(target, (int)proj.getType(), proj.getPosition());
        }

        for (auto& exp : m_explosions) {
            m_explodeShape.setPosition(exp.getPosition());
            target.draw(m_explodeShape);
        }

        m_invaders.drawInvaders(target);
        m_player.draw(target);
        m_ufo.draw(target);
    }
}//Namespace SpaceInvaders


#include <iostream>

Game::Game()
:   m_window    ({ Display::WIDTH, Display::HEIGHT}, "Space Invaders")
{
    m_window.setPosition({m_window.getPosition().x, 0});
    m_window.setFramerateLimit(60);
    pushState<SpaceInvaders::StateMainMenu>(*this);

    sf::Image icon;
    icon.loadFromFile("res/txrs/icon.png");
    m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

//Runs the main loop
void Game::run()
{
    constexpr unsigned TPS = 30; //ticks per seconds
    const sf::Time     timePerUpdate = sf::seconds(1.0f / float(TPS));
    unsigned ticks = 0;

    sf::Clock timer;
    auto lastTime = sf::Time::Zero;
    auto lag      = sf::Time::Zero;

    //Main loop of the game
    while (m_window.isOpen() && !m_states.empty()) {
        auto& state = getCurrentState();

        //Get times
        auto time = timer.getElapsedTime();
        auto elapsed = time - lastTime;
        lastTime = time;
        lag += elapsed;

        //Real time update
        state.handleInput();
        state.update(elapsed);
        counter.update();

        //Fixed time update
        while (lag >= timePerUpdate)
        {
            ticks++;
            lag -= timePerUpdate;
            state.fixedUpdate(elapsed);
        }

        //Render
        m_window.clear();
        state.render(m_window);
        counter.draw(m_window);
        m_window.display();


        //Handle window events
        handleEvent();
        tryPop();
    }
}

//Tries to pop the current game state
void Game::tryPop()
{
    if (m_shouldPop) {
        m_shouldPop = false;
        if (m_shouldExit) {
            m_states.clear();
            return;
        }
        else if (m_shouldChageState) {
            m_shouldChageState = false;
            m_states.pop_back();
            pushState(std::move(m_change));
            return;
        }
        
        m_states.pop_back();
    }
}

//Handles window events, called every frame
void Game::handleEvent()
{
    sf::Event e;

    while (m_window.pollEvent(e)) {
        getCurrentState().handleEvent(e);
        switch (e.type) {
            case sf::Event::Closed:
                m_window.close();
                break;

            default:
                break;

        }
    }
}

//Returns a reference to the current game state
StateBase& Game::getCurrentState()
{
    return *m_states.back();
}

void Game::pushState(std::unique_ptr<StateBase> state)
{
    m_states.push_back(std::move(state));
}

//Flags a boolean for the game to pop state
void Game::popState()
{
    m_shouldPop = true;
}

void Game::exitGame()
{
    m_shouldPop = true;
    m_shouldExit = true;
}


//on tin
const sf::RenderWindow& Game::getWindow() const
{
    return m_window;
}

int main()
{
    Game game;
    game.run();
}

#include <iostream>

namespace gui {

Button::Button(ButtonSize s)
{
    m_button.setOutlineThickness(1);
    m_button.setOutlineColor(sf::Color::Green);
    m_button.setFillColor(sf::Color::Black);
    switch (s) {
        case ButtonSize::Wide:
            m_button.setSize({256, 64});
            break;

        case ButtonSize::Small:
            m_button.setSize({128, 64});
            break;
    }
}

void Button::setFunction(std::function<void(void)>func)
{
    m_function = func;
}

void Button::setText (const std::string& str)
{
    m_text.setString(str);
    updateText();
}

void Button::setTexture (const sf::Texture& tex)
{
    m_button.setTexture(&tex);
}

void Button::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
    auto pos = sf::Mouse::getPosition(window);

    switch(e.type) {
        case sf::Event::MouseButtonPressed:
            switch(e.mouseButton.button) {
                case sf::Mouse::Left:
                    if (m_button.getGlobalBounds().contains((float)pos.x, (float)pos.y)) {
                        m_function();
                    }

                default:
                    break;
            }

        default:
            break;
    }
}

void Button::render(sf::RenderTarget& renderer)
{
    renderer.draw(m_button);
    renderer.draw(m_text);
}

void Button::setPosition(const sf::Vector2f& pos)
{
    m_position = pos;

    m_button.setPosition(m_position);
    m_text.setPosition  (m_position);

    updateText();
}

void Button::updateText()
{
    m_text.setOrigin(m_text.getGlobalBounds().width  / 2,
                     m_text.getGlobalBounds().height / 2);

    m_text.move(m_button.getGlobalBounds().width  / 2.0f,
                m_button.getGlobalBounds().height / 2.5f);
}


sf::Vector2f Button::getSize() const
{
    return m_button.getSize();
}

}


constexpr float BASE_Y = 95.0f;

namespace gui
{

StackMenu::StackMenu(const sf::RenderWindow& window, float baseY)
:   m_basePosition  ((float)window.getSize().x / 2.0f, baseY)
,   m_baseSize      (300, 20)
{
    m_background.setOutlineThickness(2);
    m_background.setOutlineColor(sf::Color::Green);
    m_background.setFillColor({100, 100, 100, 230});
    m_background.setSize(m_baseSize);
    m_background.setPosition(m_basePosition.x - m_baseSize.x / 2, baseY - 30);

    m_titleText.setPosition(0, baseY - 35);
    m_titleText.setOutlineColor(sf::Color::Black);
    m_titleText.setOutlineThickness(1);
    m_titleText.setCharacterSize(30);
}

StackMenu::StackMenu(const sf::Vector2f& position)
:   m_basePosition  (position)
,   m_baseSize      (300, 20)
{
    m_background.setFillColor({100, 100, 100, 128});
    m_background.setSize(m_baseSize);
    m_background.setPosition(position);
}

StackMenu::StackMenu(StackMenu&& other)
:   m_widgets       (std::move(other.m_widgets))
,   m_background    (std::move(other.m_background))
,   m_basePosition  (other.m_basePosition)
,   m_baseSize      (other.m_baseSize)
{
}

StackMenu& StackMenu::operator=(StackMenu&& other)
{
    m_widgets       =   std::move(other.m_widgets);
    m_background    =   std::move(other.m_background);
    m_basePosition  =   other.m_basePosition;
    m_baseSize      =   other.m_baseSize;

    return *this;
}

void StackMenu::addWidget(std::unique_ptr<Widget> w)
{
    initWidget(*w);
    m_widgets.push_back(std::move(w));
}

void StackMenu::initWidget(Widget& widget)
{
    widget.setPosition({m_basePosition.x - widget.getSize().x / 2,
                       m_basePosition.y});


    m_basePosition.y    += widget.getSize().y + 25;
    m_baseSize.y        += widget.getSize().y + 25;
    m_background.setSize(m_baseSize);
}

void StackMenu::setTitle(const std::string & title)
{
    m_titleText.setString(title);
    m_titleText.setPosition(Display::WIDTH / 2 - m_titleText.getGlobalBounds().width / 2,
        m_titleText.getPosition().y);
}

void StackMenu::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
    for (auto& widget : m_widgets) {
        widget->handleEvent(e, window);
    }
}

void StackMenu::render(sf::RenderTarget& renderer)
{
    renderer.draw(m_background);
    renderer.draw(m_titleText);
    for (auto& widget : m_widgets) {
        widget->render(renderer);
    }
}

}

#include <iostream>

namespace gui {

TextBox::TextBox(std::string& modString)
:   m_pModString (&modString)
{
    m_label.setCharacterSize(15);
    m_rect.setFillColor({52, 152, 219});
    m_rect.setSize({256, 64});
}

void TextBox::setLabel(const std::string& str)
{
    m_label.setString(str);
}

void TextBox::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
    handleClick     (e, window);
    handleTextInput (e);
}

void TextBox::render(sf::RenderTarget& renderer)
{
    if (!m_isActive) {
        m_rect.setFillColor({52, 152, 219});
    }
    else {
        m_rect.setFillColor({82, 132, 239});
    }
    renderer.draw(m_rect);
    renderer.draw(m_label);
    renderer.draw(m_text);
}

void TextBox::setPosition(const sf::Vector2f& pos)
{
    m_position = pos;

    m_rect.setPosition(m_position);
    m_label.setPosition(m_position.x,
                        m_position.y + m_label.getGlobalBounds().height -
                                       m_rect.getGlobalBounds().height / 2);
    m_text.setPosition  (m_position);
    m_text.move(5, m_rect.getGlobalBounds().height / 2.5f);
}

sf::Vector2f TextBox::getSize() const
{
    return  {m_rect.getSize().x,
             m_rect.getSize().y + m_label.getGlobalBounds().height};
}

void TextBox::handleClick (sf::Event e, const sf::RenderWindow& window)
{
    auto pos = sf::Mouse::getPosition(window);

    if (m_rect.getGlobalBounds().contains((float)pos.x, (float)pos.y))
    {
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                m_isActive = true;
            }
        }
    }
    else
    {
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                m_isActive = false;
            }
        }
    }
}

void TextBox::handleTextInput (sf::Event e)
{
    switch (e.type) {
    case sf::Event::TextEntered:
        if (m_isActive) {
            //Get the key that was entered
            unsigned char keyCode = e.text.unicode;

            if (isValidCharacter(keyCode)) {
                if (m_text.getGlobalBounds().width + 30 <= m_rect.getGlobalBounds().width) {
                    m_pModString->push_back(keyCode);
                }

            }
            else if (isBackspace(keyCode)) {
                //prevents popping back an empty string
                if (m_pModString->length() > 0)
                    m_pModString->pop_back();
            }
            m_text.setString(*m_pModString);
        }
        break;

    default:
        break;
    }
}

bool TextBox::isValidCharacter(unsigned char keyCode)
{
    return  keyCode >= 48 && keyCode <= 57  ||  //Numbers
            keyCode >= 65 && keyCode <= 90  ||  //Uppercase
            keyCode >= 97 && keyCode <= 122 ||  //Lowercase
            keyCode == 32;    //Space
}

bool TextBox::isBackspace(unsigned char keycode)
{
    return keycode == 8;
}


}

namespace gui {

//Text
Widget::Text::Text()
{
    setCharacterSize (25);
    setOutlineColor  (sf::Color::Black);
    setFillColor     (sf::Color::White);
    setFont          (ResourceHolder::get().fonts.get("arcade"));
}

bool Widget::Rectangle::isRolledOn(const sf::RenderWindow& window) const
{
    auto pos = sf::Mouse::getPosition(window);
    return getGlobalBounds().contains((float)pos.x, (float)pos.y);
}

bool Widget::Rectangle::isClicked  (sf::Event e, const sf::RenderWindow& window)
{
    if(isRolledOn(window)) {
        if (e.type == sf::Event::MouseButtonPressed) {
            return e.mouseButton.button == sf::Mouse::Left;
        }
    }
    return false;
}

}

ResourceHolder& ResourceHolder::get()
{
    static ResourceHolder holder;
    return holder;
}

ResourceHolder::ResourceHolder()
:   fonts           ("fonts", "ttf")
,   textures        ("txrs", "png")
,   soundBuffers    ("sfx", "ogg")
{

}


Animation::Animation(unsigned frameWidth, unsigned frameHeight)
: FRAME_WIDTH   (frameWidth)
, FRAME_HEIGHT (frameHeight)
{ }

//Adds a frame...
void Animation::addFrame(unsigned index, sf::Time delay)
{
    sf::IntRect bounds;
    bounds.top = 0;
    bounds.height = FRAME_HEIGHT;
    bounds.width  = FRAME_WIDTH;
    bounds.left   = index * FRAME_WIDTH;

    m_frames.emplace_back(bounds, delay);
}

//Returns the current/active frame of the animation
const sf::IntRect& Animation::getFrame()
{
    if (m_timer.getElapsedTime() >= m_frames[m_framePointer].delay) {
        m_timer.restart();
        m_framePointer++;
        if (m_framePointer == m_frames.size())
            m_framePointer = 0;
    }

    return m_frames[m_framePointer].bounds;
}

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

std::string getFileContent(const std::string& filePath, bool throws)
{
    std::ifstream inFile(filePath);
    if (!inFile.is_open())
    {
        std::string error = "Unable to open file: " + filePath + "!";
        if (throws) {
            throw std::runtime_error(error);
        }
        else {
            std::cerr << error << '\n';
        }
    }

    std::ostringstream stream;
    stream << inFile.rdbuf();
    return stream.str();
}


#include <iostream>

FPSCounter::FPSCounter()
{
    m_text.move(0, 0);
    m_text.setOutlineColor (sf::Color::Black);
    m_text.setFillColor({255,255,255});
    m_text.setOutlineThickness  (2);
    m_text.setFont(ResourceHolder::get().fonts.get("arcade"));
    m_text.setCharacterSize(15);
}

//updates the FPS variable
void FPSCounter::update()
{
    m_frameCount++;

    if (m_delayTimer.getElapsedTime().asSeconds() > 0.2) {
        m_fps = m_frameCount / m_fpsTimer.restart().asSeconds();
        m_frameCount = 0;
        m_delayTimer.restart();
    }
}

//Draws the FPS display to the window
void FPSCounter::draw(sf::RenderTarget& renderer)
{
    m_text.setString("FPS " + std::to_string((int)m_fps));
    renderer.draw(m_text);
}

ToggleKey::ToggleKey(sf::Keyboard::Key key)
:   m_key (key)
{ }

bool ToggleKey::isKeyPressed()
{
    if (m_delayTimer.getElapsedTime().asSeconds() > 0.2) {
        if (sf::Keyboard::isKeyPressed(m_key)) {
            m_delayTimer.restart();
            return true;
        }
    }
    return false;
}

namespace SpaceInvaders
{
    AnimationRenderer::AnimationRenderer(int frameWidth, int frameHeight, float entityWidth, float entityHeight, const sf::Texture & spriteSheet)
        : m_frameWidth(frameWidth)
        , m_frameHeight(frameHeight)
    {
        m_entity.setSize({ entityWidth, entityHeight });
        m_entity.setTexture(&spriteSheet);
    }

    void AnimationRenderer::nextFrame()
    {
        m_currentFrame++;
    }

    void AnimationRenderer::renderEntity(sf::RenderTarget & renderer, int type, const sf::Vector2f & position)
    {
        //Calculate texture coords
        int texLeft = (m_currentFrame % 2) * m_frameWidth;
        int texTop = (type * m_frameHeight);

        //Reposition and draw sprite
        m_entity.setPosition(position);
        m_entity.setTextureRect({ texLeft, texTop, m_frameWidth, m_frameHeight });
        renderer.draw(m_entity);
    }
}

namespace SpaceInvaders
{
    Collidable::Collidable(float width, float height)
        : m_size(width, height)
    {}

    bool Collidable::tryCollideWith(Collidable & other)
    {
        if (getBox().intersects(other.getBox())) {
            onCollide(other);
            other.onCollide(*this);
            return true;
        }
        return false;
    }

    sf::FloatRect Collidable::getBox() const
    {
        return
        {
            getPosition().x,
            getPosition().y,
            m_size.x,
            m_size.y
        };
    }
}

namespace SpaceInvaders
{
    Explosion::Explosion(const sf::Vector2f & position)
        : m_position(position)
    {
    }

    bool Explosion::isLifeOver() const
    {
        return m_lifetimeCounter.getElapsedTime().asSeconds() >= 0.2f;
    }

    const sf::Vector2f & Explosion::getPosition() const
    {
        return m_position;
    }
}

namespace SpaceInvaders
{
    Invader::Invader(const sf::Vector2f & initialLocation, Type type)
        : Collidable(WIDTH, HEIGHT)
        , m_location(initialLocation)
        , m_type(type)
        , m_initialPosition(initialLocation)
    {
    }

    void Invader::move(float x, float y)
    {
        m_location += {x, y};
    }

    const sf::Vector2f & Invader::getPosition() const
    {
        return m_location;
    }

    bool Invader::isAlive() const
    {
        return m_isAlive;
    }

    Invader::Type Invader::getType() const
    {
        return m_type;
    }

    void Invader::onCollide(Collidable& other)
    {
        m_isAlive = false;
    }
}

namespace SpaceInvaders
{
    namespace
    {
        constexpr float BASE_Y = (float)Display::HEIGHT - 40.0f;
    }

    Player::Player()
        : Collidable(44, 32)
        , m_deathAnimation(11, 8)
    {
        m_sprite.setSize({ 44, 32 });
        m_sprite.setPosition({ Display::WIDTH / 2, BASE_Y });
        m_sprite.setTexture(&ResourceHolder::get().textures.get("si/player"));
        m_sprite.setTextureRect({ 0, 0, 11, 8 });

        for (int i = 0; i < 20; i++) {
            m_deathAnimation.addFrame(((i % 2) + 1), sf::seconds(0.1f));
        }

        m_deathSound.setBuffer(ResourceHolder::get().soundBuffers.get("si/explosion"));

    }

    void Player::restart()
    {
        m_velocity *= 0.0f;
        m_sprite.setTextureRect({ 0, 0, 11, 8 });
        m_isAlive = true;
        m_livesLeft--;
        m_sprite.setPosition({ Display::WIDTH / 2, BASE_Y });
    }

    void Player::input()
    {
        using Key = sf::Keyboard::Key;
        auto keyDown = [](sf::Keyboard::Key k) {
            return sf::Keyboard::isKeyPressed(k);
        };

        float speed = 20;
        if (keyDown(Key::A)) {
            m_velocity.x -= speed;
        }
        else if (keyDown(Key::D)) {
            m_velocity.x += speed;
        }
    }

    void Player::update(float dt)
    {
        if (m_isAlive) {
            auto w = m_sprite.getGlobalBounds().width;
            m_sprite.move(m_velocity * dt);
            m_velocity *= 0.95f;
            if (m_sprite.getPosition().x <= 0) {
                m_velocity.x = 1.0f;
                m_sprite.setPosition(1.0f, BASE_Y);
            }
            else if (m_sprite.getPosition().x + w >= Display::WIDTH) {
                m_velocity.x = -1.0f;
                m_sprite.setPosition(Display::WIDTH - 1.0f - w, BASE_Y);
            }
        }
    }

    void Player::draw(sf::RenderTarget& target)
    {
        if (!m_isAlive) {
            m_sprite.setTextureRect(m_deathAnimation.getFrame());
        }
        if (m_livesLeft >= 0) {
            target.draw(m_sprite);
        }
    }

    sf::Vector2f Player::getGunPosition() const
    {
        return
        {
            m_sprite.getPosition().x + m_sprite.getGlobalBounds().width / 2,
            m_sprite.getPosition().y
        };
    }

    const sf::Vector2f & Player::getPosition() const
    {
        return m_sprite.getPosition();
    }

    void Player::onCollide(Collidable& other)
    {
        m_isAlive = false;
        m_deathTimer.restart();
        m_deathSound.play();
    }

    int Player::getLives() const
    {
        return m_livesLeft;
    }

    bool Player::isAlive() const
    {
        return m_isAlive;
    }

    void Player::tryRevive()
    {
        if (m_deathTimer.getElapsedTime().asSeconds() >= 1.5f) {
            restart();
        }

    }

}


namespace SpaceInvaders
{
    Projectile::Projectile(const sf::Vector2f & position, Type type, Direction direction)
        : Collidable(WIDTH / 1.5, HEIGHT)
        , m_position(position)
        , m_type(type)
        , m_direction(direction)
    {
        static int ID = 0;
        m_id = ID++;
    }

    void Projectile::update(float dt)
    {
        float speed = 650 * (float)m_direction * dt;
        m_position.y += speed;
        if (m_position.y <= 0 || m_position.y >= Display::HEIGHT) {
            destroy();
        }
    }

    void Projectile::onCollide(Collidable& other)
    {
        destroy();
    }

    void Projectile::destroy()
    {
        m_isActive = false;
    }

    const sf::Vector2f & Projectile::getPosition() const
    {
        return m_position;
    }

    Projectile::Type Projectile::getType() const
    {
        return m_type;
    }

    bool Projectile::isActive() const
    {
        return m_isActive;
    }

    Projectile::Direction Projectile::getDirection() const
    {
        return m_direction;
    }

    int Projectile::getID() const
    {
        return m_id;
    }
}


#include <iostream>

namespace SpaceInvaders
{
    Shield::Shield(float x)
        : Collidable((float)SIZE, (float)SIZE)
        , m_position(x, Display::HEIGHT - 200)
    {
        using Sty = SectorStyle;
        for (float sy = 0; sy < 4; sy++) {
            for (float sx = 0; sx < 4; sx++) {
                Sty style = Sty::Square;
                int xP = (int)sx;
                int yP = (int)sy;
                if (xP == 0 && yP == 0) style = Sty::SlopeUp;
                if (xP == 3 && yP == 0) style = Sty::SlopeDown;
                if (xP == 1 && yP == 3) style = Sty::SlopeUnderUp;
                if (xP == 2 && yP == 3) style = Sty::SlopeUnderDown;

                m_sections.emplace_back(x + sx * SECT_SIZE,
                    m_position.y + sy * SECT_SIZE, style);
            }
        }
    }

    void Shield::draw(sf::RenderTarget & target)
    {
        for (auto& sect : m_sections) {
            sect.draw(target);
        }
    }

    const sf::Vector2f & Shield::getPosition() const
    {
        return m_position;
    }

    Shield::ShieldSection& Shield::getSection(int x, int y)
    {
        return m_sections[y * 4 + x];
    }

    void Shield::destroyPoint(float relX, float relY)
    {
        //Test for out of bounds
        if (relX < 0 || relX >= SIZE ||
            relY < 0 || relY >= SIZE) return;

        //Get section this is inside of
        int xIndex = (int)relX / SECT_SIZE;
        int yIndex = (int)relY / SECT_SIZE;
        auto& section = getSection(xIndex, yIndex);
        auto& sectionPos = section.getPosition();

        //Transform to find the pixel coordinate
        float sectionTopLeftX = sectionPos.x - m_position.x;
        float sectionTopLeftY = sectionPos.y - m_position.y;
        float pixelX = relX - sectionTopLeftX;
        float pixelY = relY - sectionTopLeftY;

        //DESTROY
        section.destroyArea((int)pixelX, (int)pixelY);
    }


    bool Shield::isTouching(const Projectile& projectile)
    {
        static Random<> rand;
        if (projectile.getBox().intersects(getBox())) {
            for (auto& sector : m_sections) {
                auto result = sector.isTouching(projectile);
                if ((int)result.x == -1)
                    continue;
                else { //This means the projectile is touching the shield

                    //Get coordinate of collision point relative to top left of sheild
                    result.x -= m_position.x;
                    result.y -= m_position.y;

                    //Destory around point of collision
                    for (int y = -3; y < 3; y++) {
                        for (int x = -3; x < 3; x++) {
                            float newRelativeX = result.x + x * 2;
                            float newRelativeY = result.y + y * 2;
                            destroyPoint(newRelativeX, newRelativeY);
                        }
                    }

                    //blast damge
                    float radius = 12.0f;
                    for (int i = 0; i < 35; i++) {
                        float newRelativeX = result.x + rand.getFloatInRange(-radius, radius);
                        float newRelativeY = result.y + rand.getFloatInRange(-radius, radius);
                        destroyPoint(newRelativeX, newRelativeY);
                    }
                    return true;
                }
            }
        }
        return false;
    }

    Shield::ShieldSection::ShieldSection(float tlX, float tlY, SectorStyle style)
        : Collidable((float)SECT_SIZE, (float)SECT_SIZE)
        , m_position({ tlX, tlY })
    {
        for (float y = 0; y < SECT_SIZE; y++) {
            for (float x = 0; x < SECT_SIZE; x++) {
                sf::Vertex pixel;
                pixel.color = sf::Color::Green;
                pixel.position = { x + tlX, y + tlY };
                calculatePixelCoord((int)x, (int)y, pixel, style);
            }
        }
    }

    void Shield::ShieldSection::draw(sf::RenderTarget & target)
    {
        target.draw(m_pixels.data(), m_pixels.size(), sf::Points);
    }

    const sf::Vector2f & Shield::ShieldSection::getPosition() const
    {
        return m_position;
    }

    sf::Vector2f Shield::ShieldSection::isTouching(const  Projectile & other)
    {
        for (auto& px : m_pixels) {
            if (other.getBox().contains(px.position) && px.color == sf::Color::Green) {
                return px.position;
            }
        }
        return { -1, -1 };
    }

    //Blacks out an area around the inputted point
    void Shield::ShieldSection::destroyArea(int x, int y)
    {
        for (int oY = -2; oY <= 2; oY++) {
            for (int oX = -2; oX <= 2; oX++) {
                int newX = x + oX;
                int newY = y + oY;
                if (newX < 0 || newX >= SECT_SIZE ||
                    newY < 0 || newY >= SECT_SIZE) continue;
                m_pixels[newY * SECT_SIZE + newX].color = sf::Color::Black;
            }
        }
    }

    void Shield::ShieldSection::calculatePixelCoord(int x, int y, sf::Vertex & pixel, SectorStyle style)
    {
        switch (style) {
        case SectorStyle::Square:
            m_pixels[y * SECT_SIZE + x] = pixel;
            break;

        case SectorStyle::SlopeUp:
            if (SECT_SIZE - y < x) {
                m_pixels[y * SECT_SIZE + x] = pixel;
            }
            break;

        case SectorStyle::SlopeDown:
            if (x < y) {
                m_pixels[y * SECT_SIZE + x] = pixel;
            }
            break;

        case SectorStyle::SlopeUnderUp:
            if (SECT_SIZE - x > y) {
                m_pixels[y * SECT_SIZE + x] = pixel;
            }
            break;

        case SectorStyle::SlopeUnderDown:
            if (x > y) {
                m_pixels[y * SECT_SIZE + x] = pixel;
            }
            break;
        }
    }
}


namespace SpaceInvaders
{
    namespace
    {
        constexpr float WIDTH = 72;
        constexpr float HEIGHT = 36;
        constexpr float Y_POS = 45;
    }

    UFO::UFO(Random<>& rand)
        : Collidable(WIDTH, HEIGHT)
        , m_rng(rand)
        , m_animation(16, 8)
    {
        m_sprite.setSize({ WIDTH, HEIGHT });
        m_sprite.setPosition((float)Display::WIDTH, Y_POS);
        m_sprite.setTexture(&ResourceHolder::get().textures.get("si/ufo"));

        for (int i = 0; i < 3; i++) {
            m_animation.addFrame(i, sf::seconds(0.2f));
        }
        m_flyingSound.setBuffer(ResourceHolder::get().soundBuffers.get("si/ufo_lowpitch"));
        m_flyingSound.setVolume(10);
    }

    UFO::State UFO::getState() const
    {
        return m_state;
    }

    void UFO::update(float dt)
    {
        switch (m_state) {
        case State::Destroyed:
            m_state = State::Waiting;
            break;

        case State::Flying:
            m_sprite.move(m_vx * dt, 0);
            if (getPosition().x <= -WIDTH || getPosition().x >= Display::WIDTH + WIDTH) {
                m_state = State::Waiting;
            }
            if ((int)m_flyingSound.getStatus() != (int)sf::Sound::Status::Playing ||
                m_flyingSound.getPlayingOffset() >= sf::seconds(1.5)) {
                m_flyingSound.setPlayingOffset(sf::seconds(0.2f));
                m_flyingSound.play();
            }
            break;

        case State::Waiting:
            if (m_rng.getIntInRange(1, 250) == 100) {
                m_state = State::Flying;
                m_vx = (float)m_rng.getIntInRange(-1, 1) * 200.0f;
                float xPos;
                if (m_vx >= 0) {
                    xPos = -WIDTH;
                }
                else {
                    xPos = Display::WIDTH;
                }
                m_sprite.setPosition(xPos, Y_POS);
            }
            break;
        }
    }

    void UFO::draw(sf::RenderTarget & window)
    {
        if (m_state == State::Flying) {
            m_sprite.setTextureRect(m_animation.getFrame());
            window.draw(m_sprite);
        }
    }

    const sf::Vector2f & UFO::getPosition() const
    {
        return m_sprite.getPosition();
    }

    void UFO::onCollide(Collidable & other)
    {
        m_state = State::Destroyed;
        m_sprite.setPosition(-1000, 0); //Move offscreen so it cannot be collided with projectiles
    }
}

#include <iostream>


namespace SpaceInvaders
{
    namespace
    {
        const int MAX_INVADERS = 55;
    }

    InvaderManager::InvaderManager(World& world)
        : m_stepGap(sf::seconds(0.5f))
        , m_world(world)
        , m_invaderRenderer(12, 8, Invader::WIDTH, Invader::HEIGHT,
            ResourceHolder::get().textures.get("si/invaders"))
    {
        //Layout of the invaders 
        Invader::Type types[] = {
            Invader::Type::Squid, Invader::Type::Crab, Invader::Type::Crab,
            Invader::Type::Octopus, Invader::Type::Octopus
        };
        //Add invaders into the std::vector
        const int GAP = 10;
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 11; x++) {
                //calcuate position for invader
                float invaderX = x * Invader::WIDTH + (GAP  * x * 3) + Invader::WIDTH;
                float invaderY = y * Invader::HEIGHT + (GAP * y) + Invader::HEIGHT * 4;
                m_invaders.emplace_back(sf::Vector2f{ invaderX, invaderY }, types[y]);
            }
        }

        //load sounds
        for (int i = 0; i < 4; i++) {
            m_stepSounds[i].setBuffer(
                ResourceHolder::get().soundBuffers.get("si/fastinvader" + std::to_string(i + 1)));
        }
        m_invaderKilledSound.setBuffer(
            ResourceHolder::get().soundBuffers.get("si/invaderkilled"));


    }

    void InvaderManager::tryStepInvaders()
    {
        //Only step if clock is over timer
        if (m_stepTimer.getElapsedTime() > m_stepGap) {
            m_invaderRenderer.nextFrame();
            //Calculate amount to step
            bool moveDown = false;
            float step = m_isMovingLeft ? -10.0f : 10.0f;
            if (m_moveDown) {
                step *= -1;
            }
            m_stepSounds[m_ticks++ % 4].play();

            //Move the invaders
            for (auto& invader : m_invaders) {
                if (!invader.isAlive()) continue;
                invader.move(step, 0.0f);
                if (m_moveDown) {
                    invader.move(0, Invader::HEIGHT / 2.0f);
                }
                else if (!moveDown) {
                    //Check invader position to see if all should move down
                    moveDown = testInvaderPosition(invader);
                }
            }

            if (m_moveDown) m_isMovingLeft = !m_isMovingLeft;
            m_moveDown = moveDown;
            m_stepTimer.restart();
        }
    }

    void InvaderManager::drawInvaders(sf::RenderTarget& target)
    {
        for (auto& invader : m_invaders) {
            if (!invader.isAlive()) continue;
            m_invaderRenderer.renderEntity(target, (int)invader.getType(), invader.getPosition());
        }
    }

    CollisionResult InvaderManager::tryCollideWithProjectiles(std::vector<Projectile>& projectiles)
    {
        CollisionResult result;
        std::vector<sf::Vector2f> collisionPoints;
        for (auto& projectile : projectiles) {
            for (auto& invader : m_invaders) {
                if (!invader.isAlive() || !projectile.isActive())
                    continue;
                if (projectile.tryCollideWith(invader)) {
                    m_aliveInvaders--;
                    m_invaderKilledSound.play();
                    if (m_aliveInvaders == 0) {
                        m_hasAllInvadersBeenAdded = false;
                    }
                    result.second.emplace_back(invader.getPosition());
                    result.first += ((int)invader.getType() + 1) * 100;
                    updateStepDelay();
                }
            }
        }
        return result;
    }

    sf::Vector2f InvaderManager::getRandomLowestInvaderPoint(Random<>& random)
    {
        if (m_aliveInvaders == 0) return { -1, -1 };
        //Keep looping until an invader is found
        while (true) {
            auto invaderColumn = random.getIntInRange(0, 10);
            for (int y = 4; y >= 0; y--) {
                int index = y * 11 + invaderColumn;
                auto& invader = m_invaders.at(index);
                if (invader.isAlive()) {
                    return {
                        //transform to below the invader's center
                        invader.getPosition().x + Invader::WIDTH / 2,
                        invader.getPosition().y + Invader::HEIGHT + 5
                    };
                }
            }
        }
    }

    int InvaderManager::getAliveInvadersCount() const
    {
        return m_aliveInvaders;
    }

    //Adds invaders to scene 1 at a time
    void InvaderManager::initAddInvader()
    {
        static sf::Clock delay;
        if (delay.getElapsedTime().asSeconds() > 0.02) {
            m_invaders.at(m_initY * 11 + m_initX).makeAlive();
            m_aliveInvaders++;
            m_initX++;
            if (m_initX == 11) {
                m_initX = 0;
                m_initY--;
            }
            delay.restart();
        }

        if (m_aliveInvaders == MAX_INVADERS) {
            m_hasAllInvadersBeenAdded = true;
            m_initX = 0;
            m_initY = 4;
            updateStepDelay();
        }
    }

    bool InvaderManager::areInvadersAlive() const
    {
        return m_hasAllInvadersBeenAdded;
    }

    void InvaderManager::updateStepDelay()
    {
        m_stepGap = sf::seconds((float)m_aliveInvaders / 90.0f);
    }

    bool InvaderManager::testInvaderPosition(const Invader& invader) const
    {
        if (invader.getPosition().y > Display::HEIGHT - 150) {
            m_world.setGameIsOver();
        }
        return
            (invader.getPosition().x < 15 && m_isMovingLeft) || //Check invader left
            (invader.getPosition().x + Invader::WIDTH > Display::WIDTH - 15 && !m_isMovingLeft); //Check invader right
    }
}


namespace SpaceInvaders
{
    StarryBackground::StarryBackground()
    {
        for (int i = 0; i < 500; i++) {
            sf::Vertex star;
            giveStarRandomStartLocation(star);
            star.position.y -= Display::HEIGHT;
            m_stars.push_back(star);
        }
    }

    void StarryBackground::update(float dt)
    {
        for (auto& star : m_stars) {
            star.position.y -= 250 * dt;
            if (star.position.y <= 0) {
                giveStarRandomStartLocation(star);
            }
        }
    }

    void StarryBackground::draw(sf::RenderTarget & renderer)
    {
        renderer.draw(m_stars.data(), m_stars.size(), sf::Points);
    }

    void StarryBackground::giveStarRandomStartLocation(sf::Vertex & star)
    {
        star.position = { m_rng.getFloatInRange(0, (float)Display::WIDTH),
            m_rng.getFloatInRange((float)Display::HEIGHT, (float)Display::HEIGHT  * 2.0f) };
    }
}


#include <fstream>
#include <sstream>
#include <iostream>


namespace SpaceInvaders
{
    namespace
    {
        const auto scoresPath = "res/si/scores.txt";
    }

    StateHighscores::StateHighscores(Game & game, int score)
        : StateHighscores(game)
    {
        initSubmitMenu();
        m_scoreToSubmit = score;
        m_pActiveMenu = &m_submitScoreMenu;
        m_state = State::Submitting;
    }

    StateHighscores::StateHighscores(Game & game)
        : StateBase(game, "Highscores")
        , m_submitScoreMenu(game.getWindow(), 100.0f)
        , m_highscoreMenu(game.getWindow(), Display::HEIGHT - 100.0f)
        , m_state(State::Viewing)
    {
        initViewMenu();
        m_pActiveMenu = &m_highscoreMenu;
        m_banner.setSize({ (float)Display::WIDTH, 200 });
        m_banner.setTexture(&ResourceHolder::get().textures.get("si/highscores"));
        createHighscoreView();
    }

    void StateHighscores::handleEvent(sf::Event e)
    {
        m_pActiveMenu->handleEvent(e, m_pGame->getWindow());
    }

    void StateHighscores::update(sf::Time deltaTime)
    {
        m_background.update(deltaTime.asSeconds());
    }

    void StateHighscores::render(sf::RenderTarget & renderer)
    {
        m_background.draw(renderer);
        m_pActiveMenu->render(renderer);
        if (m_state == State::Viewing) {
            for (auto& entry : m_entryBoxes) {
                entry.draw(renderer);
            }
            renderer.draw(m_banner);
        }
    }

    int StateHighscores::getHighestScore()
    {
        std::ifstream inFile(scoresPath);
        std::string buffer;

        std::getline(inFile, buffer, ',');
        std::getline(inFile, buffer, ',');
        if (buffer.empty()) return 0;
        else return std::stoi(buffer);
    }

    void StateHighscores::initViewMenu()
    {
        loadScores();

        auto backBtn = gui::makeButton();
        backBtn->setText("Main Menu");
        backBtn->setFunction([&]() {
            m_pGame->popState();
        });
        m_highscoreMenu.addWidget(std::move(backBtn));
    }

    void StateHighscores::initSubmitMenu()
    {
        auto nameTextBox = gui::makeTextBox(m_submitString);
        nameTextBox->setLabel("Click text box to enter name");

        auto submitBtn = gui::makeButton();
        submitBtn->setText("Submit Score");
        submitBtn->setFunction([&]() {
            if (!m_submitString.empty()) {
                submitScore();
                switchToViewMenu();
            }
        });


        auto backBtn = gui::makeButton();
        backBtn->setText("View HighScores");
        backBtn->setFunction([&]() {
            loadScores();
            switchToViewMenu();
        });

        m_submitScoreMenu.addWidget(std::move(nameTextBox));
        m_submitScoreMenu.addWidget(std::move(submitBtn));
        m_submitScoreMenu.addWidget(std::move(backBtn));
    }

    void StateHighscores::switchToViewMenu()
    {
        m_state = State::Viewing;
        m_pActiveMenu = &m_highscoreMenu;
        createHighscoreView();
    }

    void StateHighscores::createHighscoreView()
    {
        loadScores();
        sortScores();
        m_entryBoxes.clear();
        for (unsigned i = 0; i < m_scores.size(); i++) {
            auto& name = m_scores[i].first;
            auto score = m_scores[i].second;

            m_entryBoxes.emplace_back(i + 1, name, score);
            if (i >= 9) return; //Only show top 10 scores
        }
    }

    void StateHighscores::loadScores()
    {
        m_scores.clear();
        std::ifstream inFile(scoresPath);
        std::string line;
        int switcher = 0;
        std::string name;
        int score;
        while (std::getline(inFile, line, ',')) {
            if (switcher++ % 2 == 0) {
                name = line;
            }
            else {
                score = std::stoi(line);
                m_scores.emplace_back(std::make_pair(name, score));
            }
        }
        sortScores();
    }

    void StateHighscores::writeScores()
    {
        sortScores();
        std::ofstream outFile(scoresPath);
        for (auto& entry : m_scores) {
            outFile << entry.first << "," << entry.second << ",";
        }
    }

    void StateHighscores::sortScores()
    {
        std::sort(m_scores.begin(), m_scores.end(), [](Entry& a, Entry& b) {
            return a.second > b.second;
        });
    }

    void StateHighscores::submitScore()
    {
        loadScores();
        m_scores.emplace_back(std::make_pair(m_submitString, m_scoreToSubmit));
        writeScores();
    }

    StateHighscores::EntryBox::EntryBox(int position, const std::string & name, int score)
    {
        float size = 35;
        float y = 200 + position * (size - 2);
        m_background.setSize({ Display::WIDTH / 1.5f, size });
        m_background.setPosition({ Display::WIDTH / 2 - m_background.getGlobalBounds().width / 2, y });

        m_nameText.setCharacterSize((unsigned)size - 5);
        m_scoreText.setCharacterSize((unsigned)size - 5);

        m_nameText.setString(std::to_string(position) + "     " + name);
        m_scoreText.setString(std::to_string(score));

        m_nameText.setPosition(m_background.getPosition());
        m_scoreText.setPosition(m_background.getPosition().x +
            m_background.getGlobalBounds().width -
            m_scoreText.getGlobalBounds().width - 10,
            y);

        m_background.setOutlineThickness(2);
        m_background.setOutlineColor(sf::Color::Green);
        m_background.setFillColor(
            position % 2 == 0 ?
            sf::Color::Black :
            sf::Color{ 50, 40, 50 }
        );
    }

    void StateHighscores::EntryBox::draw(sf::RenderTarget & renderer)
    {
        renderer.draw(m_background);
        renderer.draw(m_nameText);
        renderer.draw(m_scoreText);
    }
}



namespace SpaceInvaders
{
    StateMainMenu::StateMainMenu(Game & game)
        : StateBase(game, "Main Menu")
        , m_mainMenu(game.getWindow(), Display::HEIGHT / 2 - 100)
    {
        m_banner.setSize({ (float)Display::WIDTH, 200 });
        m_banner.setTexture(&ResourceHolder::get().textures.get("si/logo"));


        auto playBtn = gui::makeButton();
        playBtn->setText("Play game");
        playBtn->setFunction([&]() {
            m_pGame->pushState<StatePlaying>(*m_pGame);
        });

        auto highscoresBtn = gui::makeButton();
        highscoresBtn->setText("Highscores");
        highscoresBtn->setFunction([&]() {
            m_pGame->pushState<StateHighscores>(*m_pGame);
        });

        auto exitBtn = gui::makeButton();
        exitBtn->setText("Exit game");
        exitBtn->setFunction([&]() {
            m_pGame->exitGame();
        });

        m_mainMenu.addWidget(std::move(playBtn));
        m_mainMenu.addWidget(std::move(highscoresBtn));
        m_mainMenu.addWidget(std::move(exitBtn));
        m_mainMenu.setTitle("Choose Action");
    }

    void StateMainMenu::handleEvent(sf::Event e)
    {
        m_mainMenu.handleEvent(e, m_pGame->getWindow());
    }

    void StateMainMenu::update(sf::Time deltaTime)
    {
        m_background.update(deltaTime.asSeconds());
    }

    void StateMainMenu::render(sf::RenderTarget & renderer)
    {
        m_background.draw(renderer);
        m_mainMenu.render(renderer);
        renderer.draw(m_banner);
    }
}


#include <iostream>



namespace SpaceInvaders
{
    StatePlaying::StatePlaying(Game& game)
        : StateBase(game, "Playing the game")
        , m_gameOverMenu(game.getWindow(), Display::HEIGHT / 3)
        , m_scoreDisplay(Display::WIDTH / 8, "Score")
        , m_highestScoreDisplay(Display::WIDTH / 2, "HighScore")
    {

        auto mmButton = std::make_unique<gui::Button>();
        mmButton->setText("Main Menu\n");
        mmButton->setFunction([&]() {
            m_pGame->popState();
        });

        auto submitBtn = std::make_unique<gui::Button>();
        submitBtn->setText("Submit Score");
        submitBtn->setFunction([&]() {
            m_pGame->changeState<StateHighscores>(*m_pGame, m_score);
        });

        auto exitButton = std::make_unique<gui::Button>();
        exitButton->setText("Exit game\n");
        exitButton->setFunction([&]() {
            m_pGame->exitGame();
        });

        m_gameOverMenu.setTitle("GAME  OVER");
        m_gameOverMenu.addWidget(std::move(mmButton));
        m_gameOverMenu.addWidget(std::move(submitBtn));
        m_gameOverMenu.addWidget(std::move(exitButton));

        m_highestScoreDisplay.update(StateHighscores::getHighestScore());
    }

    void StatePlaying::handleEvent(sf::Event e)
    {
        if (m_isGameover) {
            m_gameOverMenu.handleEvent(e, m_pGame->getWindow());
        }
    }

    void StatePlaying::handleInput()
    {
        m_world.input();
    }

    void StatePlaying::update(sf::Time deltaTime)
    {
        if (!m_isGameover) {
            m_score += m_world.update(deltaTime.asSeconds());
            m_scoreDisplay.update(m_score);

            if (m_score > m_highestScoreDisplay.getCurrentScoreDisplayed()) {
                m_highestScoreDisplay.update(m_score);
            }
        }

        m_isGameover = m_world.isGameOver();
    }


    void StatePlaying::render(sf::RenderTarget& renderer)
    {
        m_world.draw(renderer);

        m_lifeDisplay.draw(renderer, m_world.getPlayer().getLives());
        m_scoreDisplay.draw(renderer);
        m_highestScoreDisplay.draw(renderer);

        if (m_isGameover) {
            m_gameOverMenu.render(renderer);
        }
    }

    ///////////////////////////////////////////////
    //     display member functions       ///
    StatePlaying::LifeDisplay::LifeDisplay()
    {
        m_lifeStamp.setSize({ Player::WIDTH / 2, Player::WIDTH / 2 });
        m_lifeStamp.setTexture(&ResourceHolder::get().textures.get("si/player"));
        m_lifeStamp.setTextureRect({ 0, 0, 11, 8 });
        m_label.setPosition(Display::WIDTH - (Player::WIDTH * 5), 10);
        m_label.setString("LIVES");
        m_label.setOutlineThickness(0);
    }

    void StatePlaying::LifeDisplay::draw(sf::RenderTarget& window, int lives)
    {
        float xOrigin = m_label.getPosition().x +
            m_label.getGlobalBounds().width + 10;
        float yOrigin = m_label.getPosition().y +
            m_label.getGlobalBounds().height / 2;

        window.draw(m_label);
        for (int i = 0; i < lives; i++) {
            m_lifeStamp.setPosition(xOrigin + i * Player::WIDTH / 2 + i * 10, yOrigin);
            window.draw(m_lifeStamp);
        }
    }

    StatePlaying::ScoreDisplay::ScoreDisplay(float x, const std::string& text)
        : m_text(text)
        , m_centerPosition(x)
    {
        updateDisplay();
        m_label.setOutlineThickness(0);
    }

    void StatePlaying::ScoreDisplay::update(int newScore)
    {
        m_currentScore = newScore;
        updateDisplay();
    }

    void StatePlaying::ScoreDisplay::draw(sf::RenderTarget & target)
    {
        target.draw(m_label);
    }

    int StatePlaying::ScoreDisplay::getCurrentScoreDisplayed() const
    {
        return m_currentScore;
    }

    void StatePlaying::ScoreDisplay::updateDisplay()
    {
        m_label.setString(m_text + "   " + std::to_string(m_currentScore));
        m_label.setPosition(m_centerPosition - m_label.getGlobalBounds().width / 2, 15);
    }
}

namespace SpaceInvaders
{
    World::World()
        : m_projectileRenderer(4, 8, Projectile::WIDTH, Projectile::HEIGHT,
            ResourceHolder::get().textures.get("si/projectile"))
        , m_ufo(m_rng)
        , m_invaders(*this)
    {
        m_explodeShape.setSize({ 52, 28 });
        m_explodeShape.setTexture(&ResourceHolder::get().textures.get("si/explosion"));

        const int SECT_SIZE = (Display::WIDTH / 4);
        for (int i = 0; i < 4; i++) {

            m_shields.emplace_back(float(i * SECT_SIZE + SECT_SIZE / 2 - Shield::SIZE / 2));
        }

        m_playerShoot.setBuffer(ResourceHolder::get().soundBuffers.get("si/shoot"));
        m_playerShoot.setVolume(25);
    }

    void World::input()
    {
        if (m_player.isAlive()) {
            if (m_invaders.areInvadersAlive()) {
                m_player.input();
                playerProjectileInput();
            }
        }
        else {
            m_player.tryRevive();
        }
    }

    int World::update(float dt)
    {
        int score = 0;

        if (m_invaders.areInvadersAlive()) {
            m_player.update(dt);
            if (m_player.isAlive()) {
                m_invaders.tryStepInvaders();
                enemyProjectileFire();

                //pair of score gained and points of collision list
                auto collisionResult = getCollisionResult(dt);
                if (collisionResult.second.size() > 0) {
                    score += collisionResult.first;
                    for (auto& point : collisionResult.second) {
                        m_explosions.emplace_back(point);
                    }
                }

                m_ufo.update(dt);
            }

            for (auto itr = m_explosions.begin(); itr != m_explosions.end();) {
                if (itr->isLifeOver()) itr = m_explosions.erase(itr);
                else itr++;
            }
        }
        else {
            m_invaders.initAddInvader();
            m_projectiles.clear();
            m_explosions.clear();
        }
        return score;
    }

    const Player & World::getPlayer() const
    {
        return m_player;
    }

    bool World::isGameOver() const
    {
        return m_player.getLives() == -1 || m_isGameOver;
    }

    //TODO GENERALISE THESE TWO FUNCTIONS VV
    void World::playerProjectileInput()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
            m_playerShotClock.getElapsedTime().asSeconds() > 0.5f) {
            auto point = m_player.getGunPosition();
            point.y -= Projectile::HEIGHT;
            point.x -= Projectile::WIDTH / 2.0f;
            m_projectiles.emplace_back(point, Projectile::Type::Rectangle, Projectile::Direction::Up);
            m_playerShotClock.restart();
            m_playerShoot.play();
        }
    }

    void World::enemyProjectileFire()
    {
        if (m_invaderShotClock.getElapsedTime().asSeconds() >= 0.1 &&
            m_rng.getIntInRange(0, 30) == 2) {
            auto point = m_invaders.getRandomLowestInvaderPoint(m_rng);
            if ((int)point.x == -1) return;
            auto type = static_cast<Projectile::Type>(m_rng.getIntInRange(1, 2));
            m_projectiles.emplace_back(point, type, Projectile::Direction::Down);
            m_invaderShotClock.restart();
        }
    }
    //end of to-do

    CollisionResult World::getCollisionResult(float dt)
    {
        auto result = m_invaders.tryCollideWithProjectiles(m_projectiles);
        updateProjectiles(dt, result.second);

        for (auto& projectile : m_projectiles) {

            //Projectile verses sheild collisons
            for (auto& sheild : m_shields) {
                if (sheild.isTouching(projectile)) {
                    projectile.destroy();
                    result.second.emplace_back(projectile.getPosition());
                }
            }

            //Projectile verses UFO collisons
            if (m_ufo.tryCollideWith(projectile)) {
                result.second.emplace_back(projectile.getPosition());
                result.first += 200;
            }

            //Projectile verses projectile collisions
            for (auto& otherProjectile : m_projectiles) {
                if (otherProjectile.getID() != projectile.getID()) {
                    if (otherProjectile.tryCollideWith(projectile)) {
                        result.second.emplace_back(projectile.getPosition());
                    }
                }
            }
        }


        return result;
    }

    void World::updateProjectiles(float dt, std::vector<sf::Vector2f>& collisionPoints)
    {
        for (auto itr = m_projectiles.begin(); itr != m_projectiles.end();) {
            auto& projectile = *itr;
            if (!projectile.isActive()) {
                itr = m_projectiles.erase(itr);
            }
            else {
                //Test for player getting hit 
                if (projectile.tryCollideWith(m_player)) {
                    collisionPoints.emplace_back(m_player.getGunPosition());
                    m_projectiles.clear();
                    return;
                }
                projectile.update(dt);
                itr++;
            }
        }
    }

    void World::draw(sf::RenderTarget & target)
    {
        if (m_animTimer.getElapsedTime().asSeconds() > 0.2) {
            m_projectileRenderer.nextFrame();
            m_animTimer.restart();
        }

        for (auto& shield : m_shields) {
            shield.draw(target);
        }

        for (auto& proj : m_projectiles) {
            m_projectileRenderer.renderEntity(target, (int)proj.getType(), proj.getPosition());
        }

        for (auto& exp : m_explosions) {
            m_explodeShape.setPosition(exp.getPosition());
            target.draw(m_explodeShape);
        }

        m_invaders.drawInvaders(target);
        m_player.draw(target);
        m_ufo.draw(target);
    }
}//Namespace SpaceInvaders
