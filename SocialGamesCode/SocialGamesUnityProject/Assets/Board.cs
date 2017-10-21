using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Board : MonoBehaviour {

    // Use this for 
    private bool PlayerOneTurn = true;
    public PlayDeck Deck1, Deck2;
    private Card[][] GameBoard;
    public float CameraMoveSpeed, CameraZoomMax;
    private Vector3 FirstPosition, Move , BottomLeft1, BottomLeft2, TopLeft3;
    private float DefaultCameraZoom, MainLandPanPriv1, MainLandPanPriv2;
    public float ratio, MainLandPan;
    public float CardWidth, CardHeight;
    public GameObject TempCard;
    public Vector3 Position1, Position2, ClickPosition1, ClickPosition2;
    private int BoardWidth, BoardHeight;
    public Vector2 SpawnLocation;
    private bool clicked, released, playedCard;
    public float counter;
	void Start ()
    {
        Deck1 = GameObject.FindGameObjectWithTag("Deck1").GetComponent<PlayDeck>();
        Deck2 = GameObject.FindGameObjectWithTag("Deck2").GetComponent<PlayDeck>();
        //Deck1.GetComponent<PlayDeck>().SpawnMainLand(0, 0, 3, 3);
        StartCoroutine(LateStart(0.2f, Deck1, Deck2));
        FirstPosition = new Vector3(0, 0, 0);
        DefaultCameraZoom = Camera.main.transform.position.z;
        BoardWidth = 6;
        BoardHeight = 8;
        GameBoard = new Card[BoardHeight][];
        for (int r = 0; r < BoardHeight; r++)
        {
            GameBoard[r] = new Card[BoardWidth];
            for (int c = 0; c < BoardWidth; c++)
            {
                GameBoard[r][c] = Deck1.getNullCard();
            }
        }
        MainLandPanPriv1 = -MainLandPan;
        MainLandPanPriv2 = 0;
        GetComponents<BoxCollider2D>()[1].offset = new Vector2(0, SpawnLocation.y + CardHeight * (Deck1.MainLandHeight - 1)/2 );
        GetComponents<BoxCollider2D>()[1].size = new Vector2(12, Deck1.MainLandHeight * CardHeight);
        GetComponents<BoxCollider2D>()[2].offset = new Vector2(0, -SpawnLocation.y + CardHeight * (Deck2.MainLandHeight - 3) / 2);
        GetComponents<BoxCollider2D>()[2].size = new Vector2(12, Deck2.MainLandHeight * CardHeight);
        Position1 = new Vector3(-1, -1, -1);
        Position2 = new Vector3(-1, -1, -1);
        counter = 0;
        BottomLeft1 = new Vector3(GetComponents<BoxCollider2D>()[0].bounds.min.x, GetComponents<BoxCollider2D>()[0].bounds.min.y, 0);
        BottomLeft2 = new Vector3(GetComponents<BoxCollider2D>()[1].bounds.min.x, GetComponents<BoxCollider2D>()[1].bounds.min.y, 0);
        TopLeft3 = new Vector3(GetComponents<BoxCollider2D>()[2].bounds.min.x, GetComponents<BoxCollider2D>()[2].bounds.max.y, 0);
        //Welp this works
        //int result = Deck1.GetComponent<PlayDeck>().Deck[0].AttackOtherCard(ref Deck2.GetComponent<PlayDeck>().Deck[0]);
        //print(result);
    }
	
	// Update is called once per frame
	void Update ()
    {
        if(Position1.z != -1)
        {
            //Here
        }
        //float bob = Input.GetAxis("Mouse ScrollWheel");
        if(clicked)
        {
            counter += Time.deltaTime;
        }
        else if(released && (counter < 0.2f || Mathf.Abs((ClickPosition1 - ClickPosition2).magnitude) < 100))
        {
            print("clicked");
            released = false;
            //print(TopLeft3);
            Vector3 Where = Input.mousePosition + new Vector3(0, 0, -DefaultCameraZoom);
            //print(Where);
            //print(BottomLeft);
            Where = Camera.main.ScreenToWorldPoint(Where);
            for (int r = 0; r < BoardHeight; r++)
            {
                //Instantiate(TempCard, new Vector3(0, r * CardHeight + BottomLeft.y + CardHeight / 2, 0), Quaternion.identity);
                if (Where.y > r * CardHeight + BottomLeft1.y && Where.y < (r + 1) * CardHeight + BottomLeft1.y)
                {
                    for (int c = 0; c < BoardWidth; c++)
                    {
                        //Instantiate(TempCard, new Vector3(c * CardWidth + BottomLeft.x + CardWidth / 2, 0, 0), Quaternion.identity);
                        if (Where.x > c * CardWidth + BottomLeft1.x && Where.x < (c + 1) * CardWidth + BottomLeft1.x)
                        {
                            if (Position1.x != -1)
                            {
                                if (Position1.z != 0)
                                {
                                    Position2 = new Vector3(c, r, 0);
                                    if (Position1 == Position2)
                                    {
                                        Position2 = new Vector3(-1, -1, -1);
                                    }
                                        //Selected = GameBoard[r][c];
                                }
                                else
                                {
                                        //Check to see if Position 2 if within range of Position 1
                                    if ((Position1 - new Vector3(c, r, 0)).magnitude <= GameBoard[(int)Position1.y][(int)Position1.x].MovementDistance)
                                    {
                                        Position2 = new Vector3(c, r, 0);
                                        if (Position1 == Position2)
                                        {
                                            Position2 = new Vector3(-1, -1, -1);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                if(GameBoard[r][c].Name != "")
                                {
                                    Position1 = new Vector3(c, r, 0);
                                }
                            }
                        }
                    }
                }

            }
            if (PlayerOneTurn)
            {
                for (int r = 0; r < Deck1.MainLandHeight; r++)
                {

                    //Instantiate(TempCard, new Vector3(0, r * CardHeight + BottomLeft.y + CardHeight / 2, 0), Quaternion.identity);
                    if (Where.y < r * -CardHeight + TopLeft3.y && Where.y > (r + 1) * -CardHeight + TopLeft3.y)
                    {
                        for (int c = 0; c < Deck1.MainLandWidth; c++)
                        {
                            //Instantiate(TempCard, new Vector3(c * CardWidth + BottomLeft.x + CardWidth / 2, 0, 0), Quaternion.identity);
                            if (Where.x > c * CardWidth + TopLeft3.x && Where.x < (c + 1) * CardWidth + TopLeft3.x)
                            {
                                if (Position1.x == -1)
                                {
                                    print("k");
                                    if (Deck1.IsPlayable(r, c))
                                    {
                                        Position1 = new Vector3(c, r, 1);
                                    }
                                }
                            }
                        }
                    }

                }
            }
            else
            {
                for (int r = 0; r < Deck2.MainLandHeight; r++)
                {

                    //Instantiate(TempCard, new Vector3(0, r * CardHeight + BottomLeft.y + CardHeight / 2, 0), Quaternion.identity);
                    if (Where.y > r * CardHeight + BottomLeft2.y && Where.y < (r + 1) * CardHeight + BottomLeft2.y)
                    {
                        for (int c = 0; c < Deck2.MainLandWidth; c++)
                        {
                            //Instantiate(TempCard, new Vector3(c * CardWidth + BottomLeft.x + CardWidth / 2, 0, 0), Quaternion.identity);
                            if (Where.x > c * CardWidth + BottomLeft2.x && Where.x < (c + 1) * CardWidth + BottomLeft2.x)
                            {
                                if (Position1.x == -1)
                                {
                                    print("k");
                                    if (Deck2.IsPlayable(r, c))
                                    {
                                        Position1 = new Vector3(c, r, 2);
                                    }
                                }
                            }
                        }
                    }

                }
            }
            print(Position1);
            print(Position2);
        }
        if(!clicked && released)
        {
            released = false;
            counter = 0;
        }


        if(Position2.x != -1)
        {
            MakeMove();
            Position1 = new Vector3(-1, -1, -1);
            Position2 = new Vector3(-1, -1, -1);
        }
        Camera.main.transform.position += new Vector3( 0, 0, Input.GetAxis("Mouse ScrollWheel") * 5);
        if (Camera.main.transform.position.z < DefaultCameraZoom)
        {
            Camera.main.transform.position = new Vector3(Camera.main.transform.position.x, Camera.main.transform.position.y, DefaultCameraZoom);
        }
        if (Camera.main.transform.position.z > CameraZoomMax)
        {
            Camera.main.transform.position = new Vector3(Camera.main.transform.position.x, Camera.main.transform.position.y, CameraZoomMax);
        }
        if(Input.GetKeyDown("f"))
        {
                SwitchTurns();
        }
        if (Input.GetMouseButton(0))
        {
            FirstPosition = Move;
            Move = Input.mousePosition;
            Camera.main.transform.position -= (Move - FirstPosition) * CameraMoveSpeed;

        }
        else
        {
            Move = Input.mousePosition;
        }
        float Clamper = Camera.main.transform.position.z - DefaultCameraZoom;
        Camera.main.transform.position = new Vector3(Mathf.Clamp(Camera.main.transform.position.x, -Clamper * ratio, Clamper * ratio), Mathf.Clamp(Camera.main.transform.position.y, -Clamper * ratio * 1.78f +MainLandPanPriv1, Clamper * ratio * 1.78f + MainLandPanPriv2), Camera.main.transform.position.z);


    }
    IEnumerator LateStart(float waitTime, PlayDeck Decker1, PlayDeck Decker2)
    {
        print("Waiting");
        yield return new WaitForSeconds(waitTime);
        Decker1.SpawnMainLand(SpawnLocation.x, -SpawnLocation.y, CardWidth, CardHeight, 1);
        Decker2.SpawnMainLand(SpawnLocation.x, SpawnLocation.y, CardWidth, -CardHeight, 2);
        print("Spawning MainLand");
    }
    void OnMouseUp()
    {
        clicked = false;
        released = true;
        ClickPosition1 = Input.mousePosition;
    }
    void OnMouseDown()
    {
        clicked = true;
        ClickPosition2 = Input.mousePosition;
    }
    void MakeMove()
    {
        //Trying to play card
        print(!GameBoard[(int)Position1.y][(int)Position1.x].HasMadeMove);
        if (!GameBoard[(int)Position1.y][(int)Position1.x].HasMadeMove)
        {
            if (Position1.z == 1 && Position2.z == 0 && PlayerOneTurn)
            {
                print("Trying to play card from Deck1");
                //print(Deck1.IsPlayable((int)Position1.y, (int)Position1.x));
                if (Deck1.IsPlayable((int)Position1.y, (int)Position1.x) && GameBoard[(int)Position2.y][(int)Position2.x].Name == "" && !playedCard)
                {
                    print("Successful");
                    PlayCard();
                }
                else
                {
                    print("Unsuccessful");
                }
            }
            if (Position1.z == 2 && Position2.z == 0 && !PlayerOneTurn)
            {
                print("Trying to play card from Deck2");
                //print(Deck1.IsPlayable((int)Position1.y, (int)Position1.x));
                if (Deck2.IsPlayable((int)Position1.y, (int)Position1.x) && GameBoard[(int)Position2.y][(int)Position2.x].Name == "" && !playedCard)
                {
                    print("Successful");
                    PlayCard();
                }
                else
                {
                    print("Unsuccessful");
                }
            }

            else if (Position1.z == 0 && Position2.z == 0)
            {
                if (GameBoard[(int)Position1.y][(int)Position1.x].Name != "" && GameBoard[(int)Position2.y][(int)Position2.x].Name != "")
                {
                    print("Attacking");
                    GameBoard[(int)Position1.y][(int)Position1.x].HasMadeMove = true;
                    int result = GameBoard[(int)Position1.y][(int)Position1.x].AttackOtherCard(ref GameBoard[(int)Position2.y][(int)Position2.x]);
                    if (result == 1 || result == 3)
                    {
                        Destroy(GameBoard[(int)Position1.y][(int)Position1.x].Image);
                        GameBoard[(int)Position1.y][(int)Position1.x] = Deck1.getNullCard();
                    }
                    if (result == 2 || result == 3)
                    {
                        Destroy(GameBoard[(int)Position2.y][(int)Position2.x].Image);
                        GameBoard[(int)Position2.y][(int)Position2.x] = Deck1.getNullCard();
                    }
                }
                else if (GameBoard[(int)Position1.y][(int)Position1.x].Name != "" && GameBoard[(int)Position2.y][(int)Position2.x].Name == "")
                {
                    print("Moving");
                    MoveCard();
                }
            }
            else
            {
                print("Error with that move");
            }
        }
    }
    public void PlayCard()
    {
        playedCard = true;
        Vector3 Place = new Vector3(Position2.x * CardWidth + BottomLeft1.x + CardWidth / 2, Position2.y * CardHeight + BottomLeft1.y + CardHeight / 2, 0);
        if ((int)Position1.z == 1)
        {
            GameBoard[(int)Position2.y][(int)Position2.x] = Deck1.PlayCard((int)Position1.x);
            GameBoard[(int)Position2.y][(int)Position2.x].Image = Instantiate(GameBoard[(int)Position2.y][(int)Position2.x].Image, Place, Quaternion.identity) as GameObject;
        }
        else if ((int)Position1.z == 2)
        {
            GameBoard[(int)Position2.y][(int)Position2.x] = Deck2.PlayCard((int)Position1.x);
            GameBoard[(int)Position2.y][(int)Position2.x].Image = Instantiate(GameBoard[(int)Position2.y][(int)Position2.x].Image, Place, Quaternion.identity) as GameObject;
        }
        else
        {
            print("Error");
        }
        //GameBoard[(int)Position2.y][(int)Position2.x].UpdateCard();
        //GameBoard[(int)Position2.y][(int)Position2.x].TempReveil();
    }
    public void MoveCard()
    {
        Vector3 BottomLeft1 = new Vector3(GetComponents<BoxCollider2D>()[0].bounds.min.x, GetComponents<BoxCollider2D>()[0].bounds.min.y, 0);
        Vector3 Place = new Vector3(Position2.x * CardWidth + BottomLeft1.x + CardWidth / 2, Position2.y * CardHeight + BottomLeft1.y + CardHeight / 2, 0);
        GameBoard[(int)Position2.y][(int)Position2.x] = GameBoard[(int)Position1.y][(int)Position1.x];
        GameBoard[(int)Position2.y][(int)Position2.x].HasMadeMove = true;
        GameBoard[(int)Position1.y][(int)Position1.x] = Deck1.getNullCard();
        GameBoard[(int)Position2.y][(int)Position2.x].Image.transform.position = Place;
        //I don't think i need to update this for a move function
        //GameBoard[(int)Position2.y][(int)Position2.x].UpdateCard();
    }
    public void SwitchTurns()
    {

        if (PlayerOneTurn)
        {
            PlayerOneTurn = false;
            Camera.main.transform.position = new Vector3(0, 0, DefaultCameraZoom);
            MainLandPanPriv1 = 0;
            MainLandPanPriv2 = MainLandPan;
            print("stuff");
            playedCard = false;
            for (int r = 0; r < BoardHeight; r++)
            {
                for (int c = 0; c < BoardWidth; c++)
                {
                    print("stuff2");
                    if(GameBoard[r][c].Name != "")
                    {
                        if (GameBoard[r][c].Deck == 2)
                        {
                            GameBoard[r][c].TempReveil();
                        }
                        else
                        {
                            GameBoard[r][c].UpdateCard();
                        }
                    }
                }
            }
            print(PlayerOneTurn);

        }
        else
        {
           PlayerOneTurn = true;
           Camera.main.transform.position = new Vector3(0, 0, DefaultCameraZoom);
           MainLandPanPriv1 = -MainLandPan;
           MainLandPanPriv2 = 0;
            print("stuff");
            playedCard = false;
            for (int r = 0; r < BoardHeight; r++)
            {
                for (int c = 0; c < BoardWidth; c++)
                {
                    print("stuff2");
                    if (GameBoard[r][c].Name != "")
                    {
                        print(r);
                        print(c);
                        if (GameBoard[r][c].Deck == 1)
                        {
                            GameBoard[r][c].TempReveil();
                        }
                        else
                        {
                            GameBoard[r][c].UpdateCard();
                        }
                    }
                }
            }
            print(PlayerOneTurn);

        }
        Position1 = new Vector3(-1, -1, -1);
        Position2 = new Vector3(-1, -1, -1);
    }
}
