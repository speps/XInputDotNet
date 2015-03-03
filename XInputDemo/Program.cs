using System;
using System.Threading;
using XInputDotNetPure;

namespace XInputDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                GamePadState state = GamePad.GetState(PlayerIndex.One);
                Console.WriteLine("IsConnected {0} Packet #{1}", state.IsConnected, state.PacketNumber);
                Console.WriteLine("\tTriggers {0} {1}", state.Triggers.Left, state.Triggers.Right);
                Console.WriteLine("\tD-Pad {0} {1} {2} {3}", state.DPad.Up, state.DPad.Right, state.DPad.Down, state.DPad.Left);
                Console.WriteLine("\tButtons Start {0} Back {1} LeftStick {2} RightStick {3} LeftShoulder {4} RightShoulder {5} Guide {6} A {7} B {8} X {9} Y {10}",
                    state.Buttons.Start, state.Buttons.Back, state.Buttons.LeftStick, state.Buttons.RightStick, state.Buttons.LeftShoulder, state.Buttons.RightShoulder,
                    state.Buttons.Guide, state.Buttons.A, state.Buttons.B, state.Buttons.X, state.Buttons.Y);
                Console.WriteLine("\tSticks Left {0} {1} Right {2} {3}", state.ThumbSticks.Left.X, state.ThumbSticks.Left.Y, state.ThumbSticks.Right.X, state.ThumbSticks.Right.Y);
                GamePad.SetVibration(PlayerIndex.One, state.Triggers.Left, state.Triggers.Right);
                Thread.Sleep(16);
            }
        }
    }
}
