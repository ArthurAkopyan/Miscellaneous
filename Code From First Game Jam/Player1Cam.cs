using UnityEngine;
using System.Collections;

public class Player1Cam : MonoBehaviour {

    // Use this for initialization
    void Start()
    {
        transform.position = new Vector3(-4.45f, GameObject.Find("Player1").transform.position.y+3.3f, -10);
    }

    // Update is called once per frame
    void Update()
    {
        if (!GameObject.Find("Player1").GetComponent<Player1>().CameraLock)
        {
            transform.position = new Vector3(-4.45f, GameObject.Find("Player1").transform.position.y + 3.3f, -10);
        }
        else
        {
            transform.position = new Vector3(-4.45f, 147.9f, -10f);
        }
    }
}
