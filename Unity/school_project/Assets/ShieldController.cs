using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShieldController : MonoBehaviour {

    [SerializeField]
    private float rotationPerSecond = 30.0f;

    public string protectAgainst = "EnemyProjectile";

    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag(protectAgainst))
        {
            Destroy(other.gameObject);
        }
    }

    private void Update()
    {
        //rotate shield around Z;
        transform.rotation *= Quaternion.Euler(new Vector3(0, 0, rotationPerSecond * Time.deltaTime));

    }
}
