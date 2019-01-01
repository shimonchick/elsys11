using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BossController : MonoBehaviour {

    [SerializeField]
    Transform target;

    [SerializeField]
    float movementSpeed = 0.1f;

    public float delay = 0.5f;
    public float rotationTime = 0.5f;


    private Weapon weapon;
    private float nextActionTime;
    private float currentRotationTime;
    private void Start()
    {
        weapon = GetComponent<Weapon>();
        nextActionTime = Time.time;
        currentRotationTime = 0.0f;
    }
    private void Update () {

        //Vector2 direction = Random.insideUnitCircle;
        //GetComponent<Rigidbody>().MovePosition(direction * movementSpeed * Time.deltaTime);


        Quaternion newRotation = Quaternion.LookRotation(target.position);
        transform.rotation = Quaternion.Slerp(transform.rotation, newRotation, currentRotationTime);
        currentRotationTime = currentRotationTime + Time.deltaTime;
        currentRotationTime /= rotationTime;
            
        weapon.Shoot();

	}
}
