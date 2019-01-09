using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DamageDealer : MonoBehaviour {
    public List<string> TagsToHit;

	void OnCollisionEnter(Collision collision)
	{
        foreach (string TagToHit in TagsToHit)
        {
            if (collision.gameObject.CompareTag(TagToHit))
            {
                Destroy(gameObject);
                HitReceiver hitReceiver = collision.gameObject.GetComponent<HitReceiver>();
                if (hitReceiver)
                {
                    hitReceiver.ReceiveHit(gameObject);

                }
                else
                {
                    Destroy(collision.gameObject);
                }

            }
        }
	}
}
