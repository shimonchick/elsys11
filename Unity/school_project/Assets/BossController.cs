using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BossController : MonoBehaviour {

    [SerializeField]
    Transform target;

    [SerializeField]
    float movementSpeed = 0.1f;
    [Range(0, 1)]
    public float rageModeHPMissing = 0.7f;

    public float delay = 0.5f;
    public float rotationTime = 1.0f;


    private Weapon weapon;
    private float nextActionTime;
    private float currentRotationTime;
    private HitReceiver hitReceiver;

    private void Start()
    {
        weapon = GetComponent<Weapon>();
        hitReceiver = GetComponent<HitReceiver>();
        nextActionTime = Time.time;
        currentRotationTime = 0.0f;
    }
    private void Update () {

        //Vector2 direction = Random.insideUnitCircle;
        //GetComponent<Rigidbody>().MovePosition(direction * movementSpeed * Time.deltaTime);



        transform.rotation = Quaternion.Lerp(transform.rotation, newRotation, currentRotationTime);
        currentRotationTime = Time.time * rotationTime % 1.0f;
        if((float)hitReceiver.currentHits / (float)hitReceiver.hitsToKill < rageModeHPMissing)
        {
            weapon.Shoot();
        }
        else
        {
            weapon.Shoot3();
        }

	}
}
