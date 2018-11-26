using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    public float PlayerSpeed = 0.2f;
    void Update()
    {
        float verticalInput = Input.GetAxis("Vertical");
        float horizontalInput = Input.GetAxis("Horizontal");
        float playerCameraOffset = Camera.main.transform.position.y - transform.position.y;
        Vector3 mousePositionScreenSpace = new Vector3(Input.mousePosition.x, Input.mousePosition.y, playerCameraOffset);
        Vector3 mousePositionWorldSpace = Camera.main.ScreenToWorldPoint(mousePositionScreenSpace);
        transform.LookAt(mousePositionWorldSpace);

        Vector3 direction = new Vector3(horizontalInput, 0, verticalInput);
        direction = transform.rotation * direction;
        direction = direction * PlayerSpeed * Time.deltaTime;
        transform.position += direction;
    }

}