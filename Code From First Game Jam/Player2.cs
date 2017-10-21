using UnityEngine;
using System.Collections;
//Input.GetKey ("f");
public class Player2 : MonoBehaviour
{
	public GameObject obstSound1;
	public GameObject obstSound2;
	public GameObject obstSound3;
	public GameObject obstSound4;
	public GameObject obstSound5;

	public float Acceleration, Left, Right, Up;
    private Vector3 Movement;
    public float MaxSpeed;
    private int slow, slow2 = 0, boost;
    private float PublicShit;
    public float slowAmount, slowTime;
    private bool Boost = false;
    public bool CameraLock = false;
    void Start()
    {
        transform.position = new Vector3(3, 0, 0);
        Left = 0;
        Right = 0;
    }
    void Update()
    {
        if (transform.position.y < 144.9f)
        {
                if (Input.GetKey("left") && transform.position.x > 2)
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
                if (Input.GetKey("right") && transform.position.x < 7.9)
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
            
            transform.Translate(new Vector3(Right - Left, Up - PublicShit, 0)*Time.deltaTime*60);
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
                if (boost <= 0)
                {
                    Boost = false;
                }
            }
            else
            {
                Up = 0.15f;
            }
        }
        else
        {
            CameraLock = true;
            GetComponent<Animator>().enabled = false;
            if(GameObject.Find("Player1").GetComponent<Player1>().Win == 0)
            {
                GameObject.Find("Player1").GetComponent<Player1>().Win = 2;
            }
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
