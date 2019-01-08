using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerShip : Ship {


	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        UpdateShootInputs();

    }

    private void FixedUpdate()
    {
        float verticalInput = Input.GetAxis("Vertical");
        float horizontalInput = Input.GetAxis("Horizontal");

        float playerCameraOffset = Camera.main.transform.position.y - transform.position.y;
        Vector3 mousePositionScreenSpace = new Vector3(Input.mousePosition.x, Input.mousePosition.y, playerCameraOffset);
        Vector3 mousePositionWorldSpace = Camera.main.ScreenToWorldPoint(mousePositionScreenSpace);

        Move(verticalInput, horizontalInput);
        LookTarget(mousePositionWorldSpace);


    }
    private void UpdateShootInputs()
    {
        if (Input.GetButton("Fire1"))
        {
            Shoot();
        }
    }

}
