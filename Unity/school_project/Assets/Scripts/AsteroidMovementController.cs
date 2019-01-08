using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AsteroidMovementController : MonoBehaviour {
    public float AsteroidSpeed = 2;
    public float AsteroidAngularSpeed = 2;
	public Vector3 InitialDirection = Vector3.zero;
    public float followInterval = 2.0f;
    private GameObject target;


    private float timeUntillFollowingPlayer;
    
    private float startTime;
	// Use this for initialization
	void Start () {

        timeUntillFollowingPlayer = Time.time + followInterval;
		Vector3 direction3d = InitialDirection;

		if (direction3d.sqrMagnitude < Mathf.Epsilon * Mathf.Epsilon) {
			
			Vector2 direction2d = Random.insideUnitCircle;
			direction2d.Normalize ();
			direction3d = new Vector3 (direction2d.x, 0, direction2d.y);
		}
        //Vector3 targetPosition = target.transform.position;
        //Vector3 direction = (targetPosition - transform.position).normalized;
        //direction = Vector3.RotateTowards(direction, Vector3.forward * Random.Range(-45, 45), float.MaxValue, float.MaxValue);
        
        var rb = GetComponent<Rigidbody> ();
		rb.velocity = direction3d * AsteroidSpeed;

		rb.angularVelocity = Random.onUnitSphere.normalized * AsteroidAngularSpeed;
        
    }
    private void Update()
    {
        if (!target)
        {
            
            return;
        }
        if(Time.time > timeUntillFollowingPlayer)
        {
            
            Vector3 targetPosition = target.transform.position;
            Vector3 direction = (targetPosition - transform.position).normalized;
            //direction = Vector3.RotateTowards(direction, Vector3.forward * Random.Range(-45, 45), float.MaxValue, float.MaxValue);
            direction = Quaternion.AngleAxis(Random.Range(-45,45), Vector3.up) * direction;

            var rb = GetComponent<Rigidbody>();
            rb.velocity = direction * AsteroidSpeed;

            timeUntillFollowingPlayer += followInterval;
        }
    }

    public void SetTarget(GameObject targetParam)
    {
        target = targetParam;
    }

}
