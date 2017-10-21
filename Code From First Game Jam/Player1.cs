using UnityEngine;
using System.Collections;
//Input.GetKey ("f");
public class Player1 : MonoBehaviour
{
	public GameObject obstSound1;
	public GameObject obstSound2;
	public GameObject obstSound3;
	public GameObject obstSound4;
	public GameObject obstSound5;

	public float Acceleration,Left,Right,Up;
    private Vector3 Movement;
    public float MaxSpeed;
    public int Win = 0;
    private int slow = 0,boost;
    private float PublicShit;
    public float slowAmount,slowTime;
    private bool Boost = false;
    public bool CameraLock = false;
    public GameObject Tile;
    public GameObject Final;
    public GameObject[] Obsticles = new GameObject[5];
    
    Animator Stuff;
    void Start()
    {
        Screen.SetResolution(1920, 1080, true, 60);
        Stuff = GetComponent<Animator>();
        transform.position = new Vector3(-3, 0, 0);
        Left = 0;
        Right = 0;
        Application.targetFrameRate = 60;
        for(int i = 0; i < 45; i++)
        {
            Instantiate(Obsticles[(int)(5*(Random.value))],new Vector3(-8f+6f*Random.value, 6f + 3.0f* i - 2*Random.value,0),Quaternion.identity);
        }
        for (int i = 0; i < 45; i++)
        {
            Instantiate(Obsticles[(int)(5 * (Random.value))], new Vector3(2f + 6f * Random.value, 6f + 3.0f * i - 2 * Random.value, 0), Quaternion.identity);
        }
        for (int i = 0; i < 15; i++)
        {
            Instantiate(Tile, new Vector3(0, 9.95f * i, 0), Quaternion.identity);
        }
        Instantiate(Final, new Vector3(0, 148.5f, 0), Quaternion.identity);
    }
    void Update()
    {
        if (transform.position.y < 144.9f)
        {
                if (Input.GetKey("a") && transform.position.x > -7.9)
                {
                    if (Left < MaxSpeed)
                    {
                        Left = Left + Acceleration;
                    }
                }
                else
                {
                    if (Left > 0.1)
                    {
                        Left = Left - Acceleration * 2;
                    }
                    else
                    {
                        Left = 0;
                    }
                }
                if (Input.GetKey("d") && transform.position.x < -2)
                {
                    if (Right < MaxSpeed)
                    {
                        Right = Right + Acceleration;
                    }
                }
                else
                {
                    if (Right > 0.1)
                    {
                        Right = Right - Acceleration * 2;
                    }
                    else
                    {
                        Right = 0;
                    }
                }
            if (slow > 0)
            {
                PublicShit = slowAmount;
                slow--;
            }
            else
            {
                slow = 0;
                PublicShit = 0;
            }
            if (Boost)
            {
                Up = 0.2f;
                boost--;
                if(boost <= 0)
                {
                    Boost = false;
                }
            }
            else
            {
                Up = 0.15f;
            }

            transform.Translate(new Vector3(Right - Left, Up - PublicShit, 0)*Time.deltaTime*60);
        }
        else
        {
            CameraLock = true;
            GetComponent<Animator>().enabled = false;
            if (Win == 0)
            {
                Win = 1;
            }
            Debug.Log(Win);
        }
    }
	void OnCollisionEnter2D(Collision2D hit)
	{
		if (hit.gameObject.tag == "Obstical1")
		{
			slow = (int)(900 * Time.deltaTime);
			Instantiate(obstSound1);
		}
		if (hit.gameObject.tag == "Obstical2")
		{
			slow = (int)(1300 * Time.deltaTime);
			Instantiate(obstSound2);
		}
		if (hit.gameObject.tag == "Obstical3")
		{
			slow = (int)(1800 * Time.deltaTime);
			Instantiate(obstSound3);
		}
		if (hit.gameObject.tag == "Obstical4")
		{
			Boost = true;
			boost = (int)(2700 * Time.deltaTime);
			Instantiate(obstSound4);
		}
		if(hit.gameObject.tag == "Obstical5")
		{
			slow = (int)(5400 * Time.deltaTime);
			Instantiate(obstSound5);
		}
		
		
	}
}
