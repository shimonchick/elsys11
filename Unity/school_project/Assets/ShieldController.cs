using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShieldController : MonoBehaviour {

    [SerializeField]
    private float rotationPerSecond = 30.0f;


    public List<string> protectAgainst;

    
    private void OnCollisionEnter(Collider other)
    {
        foreach (string s in protectAgainst)
        {
            if (other.CompareTag(s))
            {
                HitReceiver hitReceiver = other.GetComponent<HitReceiver>();
                hitReceiver.ReceiveHit(gameObject);
            }
        }
    }

    private void Update()
    {
        //rotate shield around Z;
        transform.rotation *= Quaternion.Euler(new Vector3(0, 0, rotationPerSecond * Time.deltaTime));

    }

}
