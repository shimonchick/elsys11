using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShieldController : MonoBehaviour {

    [SerializeField]
    private float rotationPerSecond = 30.0f;

    [SerializeField]
    private float shieldTime = 2.0f;

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

    public void ShowShield()
    {

        StartCoroutine(ShowShield(shieldTime));
    
    }

    private IEnumerator ShowShield(float shieldTime)
    {
        FindObjectOfType<PlayerController>().GetComponent<SphereCollider>().enabled = false;
        GetComponent<MeshRenderer>().enabled = true;
        GetComponent<SphereCollider>().enabled = true;
        yield return new WaitForSeconds(shieldTime);
        GetComponent<MeshRenderer>().enabled = false;
        GetComponent<SphereCollider>().enabled = false;
        FindObjectOfType<PlayerController>().GetComponent<SphereCollider>().enabled = true;
    }
}
