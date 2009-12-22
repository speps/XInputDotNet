using UnityEngine;
using XInputDotNetPure; // Required in C#

public class XInputTest : MonoBehaviour
{
    bool playerIndexSet = false;
    PlayerIndex playerIndex;
    GamePadState state;
    GamePadState prevState;
    
    GameObject textObject;
    GameObject cubeObject;
    float cubeAngle = 0.0f;

    // Use this for initialization
    void Start()
    {
        // No need to initialize anything for the plugin
        
        // However, I need that for the purpose of the demo
        textObject = GameObject.Find("GUI Text");
        cubeObject = GameObject.Find("Cube");
    }

    // Update is called once per frame
    void Update()
    {
        // Find a PlayerIndex, for a single player game
        if (!playerIndexSet || !prevState.IsConnected)
        {
            for (int i = 0; i < 4; ++i)
            {
                PlayerIndex testPlayerIndex = (PlayerIndex)i;
                GamePadState testState = GamePad.GetState(testPlayerIndex);
                if (testState.IsConnected)
                {
                    Debug.Log(string.Format("GamePad found {0}", testPlayerIndex));
                    playerIndex = testPlayerIndex;
                    playerIndexSet = true;
                }
            }
        }

        state = GamePad.GetState(playerIndex);

        string text = "Use left stick to turn the cube\n";
        text += string.Format("IsConnected {0} Packet #{1}\n", state.IsConnected, state.PacketNumber);
        text += string.Format("\tTriggers {0} {1}\n", state.Triggers.Left, state.Triggers.Right);
        text += string.Format("\tD-Pad {0} {1} {2} {3}\n", state.DPad.Up, state.DPad.Right, state.DPad.Down, state.DPad.Left);
        text += string.Format("\tButtons Start {0} Back {1}\n", state.Buttons.Start, state.Buttons.Back);
        text += string.Format("\tButtons LeftStick {0} RightStick {1} LeftShoulder {2} RightShoulder {3}\n", state.Buttons.LeftStick, state.Buttons.RightStick, state.Buttons.LeftShoulder, state.Buttons.RightShoulder);
        text += string.Format("\tButtons A {0} B {1} X {2} Y {3}\n", state.Buttons.A, state.Buttons.B, state.Buttons.X, state.Buttons.Y);
        text += string.Format("\tSticks Left {0} {1} Right {2} {3}\n", state.ThumbSticks.Left.X, state.ThumbSticks.Left.Y, state.ThumbSticks.Right.X, state.ThumbSticks.Right.Y);
        GamePad.SetVibration(playerIndex, state.Triggers.Left, state.Triggers.Right);
        
        // Display the state information
        textObject.guiText.text = text;
        
        // Make the cube turn
        cubeAngle += state.ThumbSticks.Left.X * 25.0f * Time.deltaTime;
        cubeObject.transform.localRotation = Quaternion.Euler(0.0f, cubeAngle, 0.0f);

        prevState = state;
    }
}
