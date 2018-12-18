using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AsteroidController : MonoBehaviour {

    [SerializeField]
    float deflection_angle = 30.0f;

    [SerializeField]
    float scale_factor = 0.5f;
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
    private void OnCollisionEnter(Collision collision)
    {
        Debug.Log("Collision between asteroid and something");
        if(collision.gameObject.tag == "Player")
        {
            Destroy(gameObject);
            Destroy(collision.gameObject);
        }
        if(collision.gameObject.tag == "Projectile")
        {
            
            GameObject First = Instantiate(gameObject);
            GameObject Second = Instantiate(gameObject);

            First.transform.localScale = First.transform.localScale * scale_factor;
            Second.transform.localScale = Second.transform.localScale * scale_factor;

            First.transform.RotateAround(Vector3.forward, deflection_angle);
            Second.transform.RotateAround(Vector3.forward, -deflection_angle);

            Destroy(gameObject);
            Destroy(collision.gameObject);
            Destroy(First, 5);
            Destroy(Second, 5);
            

        }
        
    }
}
