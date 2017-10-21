using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraStuff : MonoBehaviour {
    public float  CameraMaxZ;
    private float CameraXLimit = 0, CameraYLimit = 0;
    public float speed = 0.1F;
    // Use this for initialization
    void Start ()
    {
        transform.position = new Vector3(0, 0, CameraMaxZ);
	}
	
	// Update is called once per frame
	void Update ()
    {
        if (Input.touchCount == 1 && Input.GetTouch(0).phase == TouchPhase.Moved)
        {
            Vector2 touchDeltaPosition = Input.GetTouch(0).deltaPosition;

            // Move object across XZ plane
            transform.Translate(-touchDeltaPosition.x * speed, 0, -touchDeltaPosition.y * speed);
            print(touchDeltaPosition);
        }
        else if(Input.touchCount == 2 && (Input.GetTouch(0).phase == TouchPhase.Moved || Input.GetTouch(1).phase == TouchPhase.Moved))
        {
            Vector3 First = Input.GetTouch(0).position;
            Vector3 Second = Input.GetTouch(0).position;
            float Delta = Mathf.Abs((First - Second).magnitude);
        }


    }
}
