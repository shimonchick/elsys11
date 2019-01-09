using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShieldRotator : MonoBehaviour {

    [SerializeField]
    private float rotationPerSecond = 30.0f;


    private void Update()
    {
        //rotate shield around Z;
        transform.rotation *= Quaternion.Euler(new Vector3(0, 0, rotationPerSecond * Time.deltaTime));

    }
    

}
