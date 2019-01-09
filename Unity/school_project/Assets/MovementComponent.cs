using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Rigidbody))]
public class MovementComponent : MonoBehaviour {

    public float movementSpeed = 2.0f;


    private Rigidbody rb;
    private void Start()
    {
        rb = GetComponent<Rigidbody>();
    }
    public void Move(float x, float y)
    {
        Vector3 direction = new Vector3(x, 0, y);
        direction = direction.normalized;
        direction = direction * movementSpeed * Time.deltaTime;

        rb.MovePosition(transform.position + direction);
    }

    public void LookTarget(Vector3 target)
    {
        Quaternion newRotation = Quaternion.LookRotation(target - transform.position);
        rb.MoveRotation(newRotation);
    }

}
