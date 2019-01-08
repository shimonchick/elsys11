using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BossHitReceiver : HitReceiver {
    public override void ReceiveHit(GameObject damageDealer)
    {
        base.ReceiveHit(damageDealer);
        if(currentHits == hitsToKill)
        {
            GameStateController.Instance.OnBossDied();
        }
    }
}
